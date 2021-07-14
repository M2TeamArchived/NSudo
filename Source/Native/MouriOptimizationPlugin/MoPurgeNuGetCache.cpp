/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MoPurgeNuGetCache.cpp
 * PURPOSE:   Implementation for Purge NuGet Cache
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "MouriOptimizationPlugin.h"

#include <vector>
#include <string>

namespace
{
    static void PurgeNuGetCacheWorker(
        _In_ PNSUDO_CONTEXT Context,
        _In_ LPCWSTR RootPath,
        _Inout_opt_ PUINT64 UsedSpace)
    {
        HANDLE RootHandle = ::CreateFileW(
            Mile::FormatUtf16String(
                L"\\\\?\\%s\\",
                RootPath).c_str(),
            SYNCHRONIZE |
            FILE_LIST_DIRECTORY |
            DELETE |
            FILE_READ_ATTRIBUTES |
            FILE_WRITE_ATTRIBUTES,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            nullptr,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
            nullptr);
        if (RootHandle != INVALID_HANDLE_VALUE)
        {
            Mile::HResult hr = S_OK;
            hr = Mile::EnumerateFile(
                RootHandle,
                [&](
                    _In_ Mile::PFILE_ENUMERATE_INFORMATION Information) -> BOOL
            {
                if (Mile::IsDotsName(Information->FileName))
                {
                    return TRUE;
                }

                std::wstring CurrentPath = Mile::FormatUtf16String(
                    L"%s\\%s",
                    RootPath,
                    Information->FileName);

                if (Information->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    ::PurgeNuGetCacheWorker(
                        Context,
                        CurrentPath.c_str(),
                        UsedSpace);
                    return TRUE;
                }

                HANDLE CurrentHandle = ::CreateFileW(
                    Mile::FormatUtf16String(
                        L"\\\\?\\%s",
                        CurrentPath.c_str()).c_str(),
                    SYNCHRONIZE |
                    FILE_LIST_DIRECTORY |
                    DELETE |
                    FILE_READ_ATTRIBUTES |
                    FILE_WRITE_ATTRIBUTES,
                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                    nullptr,
                    OPEN_EXISTING,
                    FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
                    nullptr);
                if (RootHandle == INVALID_HANDLE_VALUE)
                {
                    ::MoPrivatePrintFinalResult(
                        Context,
                        Mile::HResultFromLastError(FALSE),
                        Mile::FormatUtf16String(
                            L"CreateFileW(%s)",
                            CurrentPath.c_str()).c_str());

                    return TRUE;
                }

                if (UsedSpace)
                {
                    UINT64 CurrentFileSize = 0;
                    hr = Mile::GetCompressedFileSizeByHandle(
                        CurrentHandle,
                        &CurrentFileSize);
                    if (hr.IsSucceeded())
                    {
                        *UsedSpace += CurrentFileSize;
                    }
                    else
                    {
                        ::MoPrivatePrintFinalResult(
                            Context,
                            hr,
                            Mile::FormatUtf16String(
                                L"Mile::GetCompressedFileSizeByHandle(%s)",
                                CurrentPath.c_str()).c_str());
                    }
                }
                else
                {
                    hr = Mile::DeleteFileByHandleIgnoreReadonlyAttribute(
                        CurrentHandle);
                    if (hr.IsFailed())
                    {
                        ::MoPrivatePrintFinalResult(
                            Context,
                            hr,
                            Mile::FormatUtf16String(
                                L"Mile::DeleteFileByHandle"
                                L"IgnoreReadonlyAttribute(%s)",
                                CurrentPath.c_str()).c_str());
                    }
                }

                ::CloseHandle(CurrentHandle);

                return TRUE;
            });
            if (hr.IsFailed())
            {
                ::MoPrivatePrintFinalResult(
                    Context,
                    Mile::HResultFromLastError(FALSE),
                    Mile::FormatUtf16String(
                        L"Mile::EnumerateFile(%s)",
                        RootPath).c_str());
            }

            if (!UsedSpace)
            {
                hr = Mile::DeleteFileByHandleIgnoreReadonlyAttribute(
                    RootHandle);
                if (hr.IsFailed())
                {
                    ::MoPrivatePrintFinalResult(
                        Context,
                        hr,
                        Mile::FormatUtf16String(
                            L"Mile::DeleteFileByHandleIgnoreReadonlyAttribute(%s)",
                            RootPath).c_str());
                }
            }
        
            ::CloseHandle(RootHandle);
        }
        else
        {
            ::MoPrivatePrintFinalResult(
                Context,
                Mile::HResultFromLastError(FALSE),
                Mile::FormatUtf16String(
                    L"CreateFileW(%s)",
                    RootPath).c_str());
        }
    }
}

EXTERN_C HRESULT WINAPI MoPurgeNuGetCache(
    _In_ PNSUDO_CONTEXT Context)
{
    Mile::HResult hr = S_OK;
    LPCWSTR FailedPoint = nullptr;
    HANDLE PreviousContextTokenHandle = INVALID_HANDLE_VALUE;
    std::vector<std::wstring> NuGetCachePathList;

    do
    {
        DWORD PurgeMode = ::MoPrivateParsePurgeMode(Context);
        if (PurgeMode == 0)
        {
            hr = Mile::HResult::FromWin32(ERROR_CANCELLED);
            break;
        }

        if (PurgeMode != MO_PRIVATE_PURGE_MODE_SCAN &&
            PurgeMode != MO_PRIVATE_PURGE_MODE_PURGE)
        {
            hr = E_NOINTERFACE;
            break;
        }

        hr = ::MoPrivateEnableBackupRestorePrivilege(
            &PreviousContextTokenHandle);
        if (hr.IsFailed())
        {
            FailedPoint = L"MoPrivateEnableBackupRestorePrivilege";
            break;
        }

        for (std::wstring const& ProfilePath : ::MoPrivateGetProfilePathList())
        {
            std::wstring CandidatePath;

            CandidatePath = ProfilePath + L"\\AppData\\Local\\NuGet\\v3-cache";
            if (::MoPrivateIsFileExist(CandidatePath.c_str()))
            {
                NuGetCachePathList.push_back(CandidatePath);
            }

            CandidatePath = ProfilePath + L"\\AppData\\Local\\NuGet\\plugins-cache";
            if (::MoPrivateIsFileExist(CandidatePath.c_str()))
            {
                NuGetCachePathList.push_back(CandidatePath);
            }

            CandidatePath = ProfilePath + L"\\AppData\\Local\\Temp\\NuGetScratch";
            if (::MoPrivateIsFileExist(CandidatePath.c_str()))
            {
                NuGetCachePathList.push_back(CandidatePath);
            }

            CandidatePath = ProfilePath + L"\\.nuget\\packages";
            if (::MoPrivateIsFileExist(CandidatePath.c_str()))
            {
                NuGetCachePathList.push_back(CandidatePath);
            }
        }
        if (NuGetCachePathList.empty())
        {
            hr = E_NOINTERFACE;
            FailedPoint = L"MoPrivateGetProfilePathList";
            break;
        }

        UINT64 UsedSpace = 0;
        for (std::wstring const& NuGetCachePath : NuGetCachePathList)
        {
            if (PurgeMode == MO_PRIVATE_PURGE_MODE_SCAN)
            {
                ::PurgeNuGetCacheWorker(
                    Context,
                    NuGetCachePath.c_str(),
                    &UsedSpace);
            }
            else if (PurgeMode == MO_PRIVATE_PURGE_MODE_PURGE)
            {
                ::PurgeNuGetCacheWorker(
                    Context,
                    NuGetCachePath.c_str(),
                    nullptr);
            }
        }

        if (PurgeMode == MO_PRIVATE_PURGE_MODE_SCAN)
        {
            ::MoPrivatePrintPurgeScanResult(
                Context,
                UsedSpace);
        }

    } while (false);

    if (PreviousContextTokenHandle != INVALID_HANDLE_VALUE)
    {
        ::SetThreadToken(nullptr, PreviousContextTokenHandle);
        ::CloseHandle(PreviousContextTokenHandle);
    }

    ::MoPrivatePrintFinalResult(Context, hr, FailedPoint);

    return hr;
}
