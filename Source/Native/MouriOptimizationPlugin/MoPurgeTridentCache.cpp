/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MoPurgeTridentCache.cpp
 * PURPOSE:   Implementation for Purge Trident Cache
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "MouriOptimizationPlugin.h"

#include "MouriOptimizationPlugin.h"

#include <regex>
#include <vector>
#include <string>

namespace
{
    static const std::vector<std::wregex> g_TridentCacheFolderInclusionList =
    {
        std::wregex(
            L"(.*)\\\\INetCache",
            std::regex_constants::syntax_option_type::icase),
        std::wregex(
            L"(.*)\\\\Temporary Internet Files",
            std::regex_constants::syntax_option_type::icase),
        std::wregex(
            L"(.*)\\\\MicrosoftEdge\\\\Cache",
            std::regex_constants::syntax_option_type::icase)
    };

    static bool IsFileNameMatchedWithRegularExpressionList(
        std::wstring const& FileName,
        std::vector<std::wregex> const& RegularExpressionList)
    {
        for (std::wregex const& RegularExpressionItem : RegularExpressionList)
        {
            if (std::regex_match(FileName, RegularExpressionItem))
            {
                return true;
            }
        }

        return false;
    }

    void PurgeTridentCacheFolderWorker(
        _In_ PNSUDO_CONTEXT Context,
        _In_ LPCWSTR RootPath,
        _Inout_opt_ PUINT64 UsedSpace)
    {
        HANDLE RootHandle = ::MoPrivateCreateFile(
            RootPath,
            SYNCHRONIZE | FILE_LIST_DIRECTORY,
            FILE_SHARE_READ,
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

                if (!(Information->FileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                {
                    return TRUE;
                }

                std::wstring CurrentPath = Mile::FormatUtf16String(
                    L"%s\\%s",
                    RootPath,
                    Information->FileName);

                if (::IsFileNameMatchedWithRegularExpressionList(
                    CurrentPath,
                    g_TridentCacheFolderInclusionList))
                {
                    ::MoPrivateEmptyDirectoryWorker(
                        Context,
                        CurrentPath.c_str(),
                        UsedSpace);
                }
                else
                {
                    ::PurgeTridentCacheFolderWorker(
                        Context,
                        CurrentPath.c_str(),
                        UsedSpace);
                }

                return TRUE;
            });
            if (hr.IsFailed())
            {
                ::MoPrivateWriteErrorMessage(
                    Context,
                    hr,
                    L"%s(%s)",
                    L"Mile::EnumerateFile",
                    RootPath);
            }

            ::CloseHandle(RootHandle);
        }
        else
        {
            ::MoPrivateWriteErrorMessage(
                Context,
                Mile::HResultFromLastError(FALSE),
                L"%s(%s)",
                L"CreateFileW",
                RootPath);
        }
    }
}

EXTERN_C HRESULT WINAPI MoPurgeTridentCache(
    _In_ PNSUDO_CONTEXT Context)
{
    Mile::HResult hr = S_OK;
    HANDLE PreviousContextTokenHandle = INVALID_HANDLE_VALUE;
    std::vector<std::wstring> ProfilePathList;

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
            ::MoPrivateWriteErrorMessage(
                Context,
                hr,
                L"MoPrivateEnableBackupRestorePrivilege");
            break;
        }

        ProfilePathList = ::MoPrivateGetProfilePathList();
        if (ProfilePathList.empty())
        {
            hr = E_NOINTERFACE;
            ::MoPrivateWriteErrorMessage(
                Context,
                E_NOINTERFACE,
                L"MoPrivateGetProfilePathList");
            break;
        }

        UINT64 UsedSpace = 0;
        for (std::wstring const& ProfilePath : ProfilePathList)
        {
            if (PurgeMode == MO_PRIVATE_PURGE_MODE_SCAN)
            {
                ::PurgeTridentCacheFolderWorker(
                    Context,
                    ProfilePath.c_str(),
                    &UsedSpace);
            }
            else if (PurgeMode == MO_PRIVATE_PURGE_MODE_PURGE)
            {
                ::PurgeTridentCacheFolderWorker(
                    Context,
                    ProfilePath.c_str(),
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

    ::MoPrivateWriteFinalResult(Context, hr);

    return hr;
}
