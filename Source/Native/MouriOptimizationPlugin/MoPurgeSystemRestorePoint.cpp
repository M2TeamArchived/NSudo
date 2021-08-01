/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MoPurgeSystemRestorePoint.cpp
 * PURPOSE:   Implementation for Purge System Restore Point
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "MouriOptimizationPlugin.h"

#include <vss.h>
#include <vswriter.h>
#include <vsbackup.h>
#include "vsmgmt.h"

namespace
{
    /**
     * @brief Provider ID of Microsoft Software Shadow Copy Provider 1.0.
    */
    const VSS_ID ProviderId =
    {
        0xb5946137,
        0x7b9f,
        0x4925,
        { 0xaf,0x80,0x51,0xab,0xd6,0xb,0x20,0xd5 }
    }; // b5946137-7b9f-4925-af80-51abd60b20d5

    /**
     * @brief Event Type of Restore Points.
    */
    enum RESTORE_POINT_EVENT_TYPE
    {
        BeginSystemChange = 100,
        EndSystemChange,
        EndNestedSystemChange = 103,
        BeginNestedSystemChange
    };

    /**
     * @brief Type of Restore Points.
    */
    enum RESTORE_POINT_TYPE
    {
        ApplicationInstall,
        ApplicationUninstall,
        DesktopSetting,
        AccessibilitySetting,
        OESetting,
        ApplicationRun,
        Restore,
        CheckPoint,
        WindowsShutdown,
        WindowsBoot,
        DeviceDriverInstall,
        FirstRun,
        ModifySettings,
        CancelledOperation,
        BackupRecovery,
        Backup,
        ManualCheckPoint,
        WindowsUpdate,
        CriticalUpdate
    };

    /**
     * @brief For Windows Millennium compatibility.
    */
#pragma pack(push, srrestoreptapi_include)
#pragma pack(1)

    /**
     * @brief Restore point information.
    */
    typedef struct _RESTOREPTINFOW
    {
        // Type of Event - Begin or End.
        DWORD dwEventType;

        // Type of Restore Point - App install/uninstall.
        DWORD dwRestorePtType;

        // Sequence Number - 0 for begin.
        INT64 llSequenceNumber;

        // Description - Name of Application / Operation.
        WCHAR szDescription[256];

    } RESTOREPOINTINFOW, * PRESTOREPOINTINFOW;

    /**
     * @brief Status returned by System Restore.
    */
    typedef struct _SMGRSTATUS
    {
        // Status returned by State Manager Process.
        DWORD   nStatus;

        // Sequence Number for the restore point.
        INT64   llSequenceNumber;

    } STATEMGRSTATUS, * PSTATEMGRSTATUS;

#pragma pack(pop, srrestoreptapi_include)

    /**
     * @brief RPC call to set a restore point.
     * @return If the call succeeds, the return value is TRUE. If the call
     *         fails, the return value is FALSE. If pSmgrStatus nStatus field
     *         is set as follows:
     *         ERROR_SUCCESS
     *             If the call succeeded (return value will be TRUE).
     *         ERROR_TIMEOUT
     *             If the call timed out due to a wait on a mutex for setting
     *             restore points.
     *         ERROR_INVALID_DATA
     *             If the cancel restore point is called with an invalid
     *             sequence number.
     *         ERROR_INTERNAL_ERROR
     *             If there are internal failures.
     *         ERROR_BAD_ENVIRONMENT
     *             If the API is called in SafeMode.
     *         ERROR_SERVICE_DISABLED
     *             If System Restore is Disabled.
     *         ERROR_DISK_FULL
     *             If System Restore is frozen (Windows Whistler only).
     *         ERROR_ALREADY_EXISTS
     *             If this is a nested restore point.
    */

    extern "C"
    {
        BOOL WINAPI SRSetRestorePointW(
            _In_ PRESTOREPOINTINFOW pRestorePtSpec,
            _Out_ PSTATEMGRSTATUS   pSMgrStatus);

        DWORD WINAPI SRRemoveRestorePoint(
            _In_ DWORD dwRPNum);

        DWORD WINAPI EnableSR(
            _In_ LPCWSTR lpDrive);

        DWORD WINAPI DisableSR(
            _In_ LPCWSTR lpDrive);
    }

    static HRESULT QueryVssAllocatedSpace(
        _In_ LPWSTR VolumeName,
        _Out_ PUINT64 AllocatedSpace)
    {
        Mile::HResult hr = E_INVALIDARG;
        IVssSnapshotMgmt* pManagement = nullptr;
        IVssDifferentialSoftwareSnapshotMgmt* pDifferentialManagement = nullptr;
        IVssEnumMgmtObject* pEnumManagementObject = nullptr;
        VSS_MGMT_OBJECT_PROP Properties;
        ULONG Fetched;

        auto ExitHandler = Mile::ScopeExitTaskHandler([&]()
        {
            if (pEnumManagementObject)
            {
                pEnumManagementObject->Release();
            }

            if (pDifferentialManagement)
            {
                pDifferentialManagement->Release();
            }

            if (pManagement)
            {
                pManagement->Release();
            }
        });

        if (!AllocatedSpace)
        {
            return hr;
        }
        else
        {
            *AllocatedSpace = 0;
        }

        hr = ::CoCreateInstance(
            CLSID_VssSnapshotMgmt,
            nullptr,
            CLSCTX_ALL,
            IID_IVssSnapshotMgmt,
            reinterpret_cast<LPVOID*>(&pManagement));
        if (hr.IsFailed())
        {
            return hr;
        }

        hr = pManagement->GetProviderMgmtInterface(
            ProviderId,
            IID_IVssDifferentialSoftwareSnapshotMgmt,
            reinterpret_cast<IUnknown**>(&pDifferentialManagement));
        if (hr.IsFailed())
        {
            return hr;
        }

        hr = pDifferentialManagement->QueryDiffAreasOnVolume(
            VolumeName,
            &pEnumManagementObject);
        if (hr.IsFailed())
        {
            return hr;
        }

        while (S_OK == pEnumManagementObject->Next(
            1,
            &Properties,
            &Fetched))
        {
            *AllocatedSpace += Properties.Obj.DiffArea.m_llAllocatedDiffSpace;
        }

        return S_OK;
    }

    static HRESULT DeleteAllVssSnapshots()
    {
        using CreateBackupComponentsFunctionType =
            decltype(::CreateVssBackupComponentsInternal)*;
        using FreeSnapshotPropertiesFunctionType =
            decltype(::VssFreeSnapshotPropertiesInternal)*;

        Mile::HResult hr = S_OK;
        HMODULE VssModuleHandle = nullptr;
        CreateBackupComponentsFunctionType pCreateBackupComponents = nullptr;
        FreeSnapshotPropertiesFunctionType pFreeSnapshotProperties = nullptr;
        IVssBackupComponents* pVssBackup = nullptr;
        IVssEnumObject* pEnumObject = nullptr;
        VSS_OBJECT_PROP Properties;
        ULONG Fetched;

        auto ExitHandler = Mile::ScopeExitTaskHandler([&]()
        {
            if (pEnumObject)
            {
                pEnumObject->Release();
            }

            if (pVssBackup)
            {
                pVssBackup->Release();
            }

            if (VssModuleHandle)
            {
                ::FreeLibrary(VssModuleHandle);
            }
        });

        VssModuleHandle = Mile::LoadLibraryFromSystem32(L"vssapi.dll");
        if (!VssModuleHandle)
        {
            return E_NOINTERFACE;
        }

        pCreateBackupComponents =
            reinterpret_cast<CreateBackupComponentsFunctionType>(
                ::GetProcAddress(
                    VssModuleHandle,
                    "CreateVssBackupComponentsInternal"));
        if (!pCreateBackupComponents)
        {
            return E_NOINTERFACE;
        }

        pFreeSnapshotProperties =
            reinterpret_cast<FreeSnapshotPropertiesFunctionType>(
                ::GetProcAddress(
                    VssModuleHandle,
                    "VssFreeSnapshotPropertiesInternal"));
        if (!pFreeSnapshotProperties)
        {
            return E_NOINTERFACE;
        }

        hr = pCreateBackupComponents(
            &pVssBackup);
        if (hr.IsFailed())
        {
            return hr;
        }

        hr = pVssBackup->InitializeForBackup();
        if (hr.IsFailed())
        {
            return hr;
        }

        hr = pVssBackup->SetContext(
            VSS_SNAPSHOT_CONTEXT::VSS_CTX_ALL);
        if (hr.IsFailed())
        {
            return hr;
        }

        hr = pVssBackup->Query(
            GUID_NULL,
            VSS_OBJECT_TYPE::VSS_OBJECT_NONE,
            VSS_OBJECT_TYPE::VSS_OBJECT_SNAPSHOT,
            &pEnumObject);
        if (hr.IsFailed())
        {
            return hr;
        }

        while (S_OK == pEnumObject->Next(
            1,
            &Properties,
            &Fetched))
        {
            LONG lSnapshots = 0;
            VSS_ID idNonDeletedSnapshotID = GUID_NULL;

            pVssBackup->DeleteSnapshots(
                Properties.Obj.Snap.m_SnapshotId,
                VSS_OBJECT_TYPE::VSS_OBJECT_SNAPSHOT,
                FALSE,
                &lSnapshots,
                &idNonDeletedSnapshotID);

            pFreeSnapshotProperties(
                &Properties.Obj.Snap);
        }

        return S_OK;
    }

    static HRESULT CreateSystemRestorePoint(
        _In_ RESTORE_POINT_EVENT_TYPE EventType,
        _In_ RESTORE_POINT_TYPE RestorePointType,
        _In_ LPCWSTR Description)
    {
        HMODULE ModuleHandle = nullptr;
        decltype(::SRSetRestorePointW)* pSRSetRestorePointW = nullptr;

        auto ExitHandler = Mile::ScopeExitTaskHandler([&]()
        {
            if (ModuleHandle)
            {
                ::FreeLibrary(ModuleHandle);
            }
        });

        ModuleHandle = Mile::LoadLibraryFromSystem32(L"srclient.dll");
        if (!ModuleHandle)
        {
            return E_NOINTERFACE;
        }

        pSRSetRestorePointW =
            reinterpret_cast<decltype(::SRSetRestorePointW)*>(
                ::GetProcAddress(
                    ModuleHandle,
                    "SRSetRestorePointW"));
        if (!pSRSetRestorePointW)
        {
            return E_NOINTERFACE;
        }

        STATEMGRSTATUS SRStatus = { 0 };
        RESTOREPOINTINFOW RPInfo = { 0 };

        RPInfo.dwEventType = EventType;
        RPInfo.dwRestorePtType = RestorePointType;
        RPInfo.llSequenceNumber = 0;
        ::wcscpy_s(RPInfo.szDescription, 256, Description);

        if (!pSRSetRestorePointW(
            &RPInfo,
            &SRStatus))
        {
            return Mile::HResult::FromWin32(SRStatus.nStatus);
        }

        return S_OK;
    }
}

EXTERN_C HRESULT WINAPI MoPurgeSystemRestorePoint(
    _In_ PNSUDO_CONTEXT Context)
{
    Mile::HResult hr = S_OK;

    DWORD PurgeMode = ::MoPrivateParsePurgeMode(Context);
    if (PurgeMode == MO_PRIVATE_PURGE_MODE_SCAN)
    {
        std::wstring Path =
            Mile::ExpandEnvironmentStringsW(L"%SystemDrive%") + L"\\";
        UINT64 AllocatedSpace = 0;
        hr = ::QueryVssAllocatedSpace(
            const_cast<LPWSTR>(Path.c_str()),
            &AllocatedSpace);
        if (hr.IsSucceeded())
        {
            ::MoPrivatePrintPurgeScanResult(Context, AllocatedSpace);
        }
        else
        {
            ::MoPrivateWriteErrorMessage(
                Context,
                hr,
                L"QueryVssAllocatedSpace");
        }
    }
    else if (PurgeMode == MO_PRIVATE_PURGE_MODE_PURGE)
    {
        hr = ::DeleteAllVssSnapshots();
        if (hr.IsSucceeded())
        {
            hr = ::CreateSystemRestorePoint(
                RESTORE_POINT_EVENT_TYPE::BeginSystemChange,
                RESTORE_POINT_TYPE::ManualCheckPoint,
                Context->GetTranslation(
                    Context,
                    "MoPurgeSystemRestorePoint_RestorePointName"));
            if (hr.IsFailed())
            {
                ::MoPrivateWriteErrorMessage(
                    Context,
                    hr,
                    L"CreateSystemRestorePoint");
            }
        }
        else
        {
            ::MoPrivateWriteErrorMessage(
                Context,
                hr,
                L"DeleteAllVssSnapshots");
        }
    }
    else
    {
        hr = Mile::HResult::FromWin32(ERROR_CANCELLED);
    }

    ::MoPrivateWriteFinalResult(Context, hr);

    return hr;
}
