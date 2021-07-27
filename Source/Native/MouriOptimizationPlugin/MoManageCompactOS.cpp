/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MoManageCompactOS.cpp
 * PURPOSE:   Implementation for Manage Compact OS
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "MouriOptimizationPlugin.h"

#include <string>
#include <vector>

namespace
{
    static void CompressFileWorker(
        _In_ PNSUDO_CONTEXT Context,
        _In_ LPCWSTR RootPath)
    {
        HANDLE RootHandle = ::MoPrivateCreateFile(
            RootPath,
            SYNCHRONIZE | FILE_LIST_DIRECTORY,
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

                {
                    DWORD& FileAttributes = Information->FileAttributes;

                    if (FileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)
                    {
                        return TRUE;
                    }

                    if (FileAttributes & FILE_ATTRIBUTE_EA)
                    {
                        return TRUE;
                    }

                    if (FileAttributes & FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS)
                    {
                        return TRUE;
                    }
                }

                std::wstring CurrentPath = Mile::FormatUtf16String(
                    L"%s\\%s",
                    RootPath,
                    Information->FileName);

                if (S_OK == ::PathMatchSpecExW(
                    CurrentPath.c_str(),
                    L"*\\WinSxS\\Backup;"
                    L"*\\WinSxS\\ManifestCache;"
                    L"*\\WinSxS\\Manifests;"
                    L"*\\ntldr;"
                    L"*\\cmldr;"
                    L"*\\BootMgr;"
                    L"*\\aow.wim;"
                    L"*\\boot\\bcd;"
                    L"*\\boot\\bcd.*;"
                    L"*\\boot\\bootstat.dat;"
                    L"*\\config\\drivers;"
                    L"*\\config\\drivers.*;"
                    L"*\\config\\system;"
                    L"*\\config\\system.*;"
                    L"*\\windows\\bootstat.dat;"
                    L"*\\winload.e??*;"
                    L"*\\winresume.e??*;",
                    PMSF_MULTIPLE))
                {
                    ::MoPrivateWriteLine(
                        Context,
                        L"Skipped - %s.",
                        CurrentPath.c_str());

                    return TRUE;
                }

                if (Information->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    ::CompressFileWorker(
                        Context,
                        CurrentPath.c_str());
                    
                    return TRUE;
                }

                HANDLE CurrentHandle = ::MoPrivateCreateFile(
                    CurrentPath.c_str(),
                    FILE_READ_DATA | FILE_READ_ATTRIBUTES,
                    FILE_SHARE_READ | FILE_SHARE_DELETE,
                    nullptr,
                    OPEN_EXISTING,
                    FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
                    nullptr);
                if (CurrentHandle == INVALID_HANDLE_VALUE)
                {
                    ::MoPrivateWriteErrorMessage(
                        Context,
                        Mile::HResultFromLastError(FALSE),
                        L"%s(%s)",
                        L"CreateFileW",
                        CurrentPath.c_str());
                    return TRUE;
                }

                DWORD CompressionAlgorithm = 0;
                hr = Mile::GetWofCompressionAttribute(
                    CurrentHandle,
                    &CompressionAlgorithm);
                if (hr.IsFailed() ||
                    CompressionAlgorithm != FILE_PROVIDER_COMPRESSION_XPRESS4K)
                {
                    hr = Mile::SetWofCompressionAttribute(
                        CurrentHandle,
                        FILE_PROVIDER_COMPRESSION_XPRESS4K);
                    if (hr.IsSucceeded())
                    {
                        ::MoPrivateWriteLine(
                            Context,
                            L"Compressed - %s.",
                            CurrentPath.c_str());
                    }
                    else
                    {
                        ::MoPrivateWriteErrorMessage(
                            Context,
                            hr,
                            L"%s(%s)",
                            L"Mile::SetWofCompressionAttribute",
                            CurrentPath.c_str());
                    }
                }
                else
                {
                    ::MoPrivateWriteLine(
                        Context,
                        L"Skipped - %s.",
                        CurrentPath.c_str());
                }

                ::CloseHandle(CurrentHandle);

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

    static void UncompressFileWorker(
        _In_ PNSUDO_CONTEXT Context,
        _In_ LPCWSTR RootPath)
    {
        HANDLE RootHandle = ::MoPrivateCreateFile(
            RootPath,
            SYNCHRONIZE | FILE_LIST_DIRECTORY,
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

                {
                    DWORD& FileAttributes = Information->FileAttributes;

                    if (FileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)
                    {
                        return TRUE;
                    }

                    if (FileAttributes & FILE_ATTRIBUTE_EA)
                    {
                        return TRUE;
                    }

                    if (FileAttributes & FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS)
                    {
                        return TRUE;
                    }
                }

                if (Information->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    ::UncompressFileWorker(
                        Context,
                        CurrentPath.c_str());
                    return TRUE;
                }

                HANDLE CurrentHandle = ::MoPrivateCreateFile(
                    CurrentPath.c_str(),
                    FILE_READ_DATA | FILE_READ_ATTRIBUTES,
                    FILE_SHARE_READ | FILE_SHARE_DELETE,
                    nullptr,
                    OPEN_EXISTING,
                    FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,
                    nullptr);
                if (CurrentHandle == INVALID_HANDLE_VALUE)
                {
                    ::MoPrivateWriteErrorMessage(
                        Context,
                        Mile::HResultFromLastError(FALSE),
                        L"%s(%s)",
                        L"CreateFileW",
                        CurrentPath.c_str());
                    return TRUE;
                }

                DWORD CompressionAlgorithm = 0;
                hr = Mile::GetWofCompressionAttribute(
                    CurrentHandle,
                    &CompressionAlgorithm);
                if (hr.IsSucceeded())
                {
                    hr = Mile::RemoveWofCompressionAttribute(CurrentHandle);
                    if (hr.IsSucceeded())
                    {
                        ::MoPrivateWriteLine(
                            Context,
                            L"Uncompressed - %s.",
                            CurrentPath.c_str());
                    }
                    else
                    {
                        ::MoPrivateWriteErrorMessage(
                            Context,
                            hr,
                            L"%s(%s)",
                            L"Mile::RemoveWofCompressionAttribute",
                            CurrentPath.c_str());
                    }
                }
                else
                {
                    ::MoPrivateWriteLine(
                        Context,
                        L"Skipped - %s.",
                        CurrentPath.c_str());
                }
                
                ::CloseHandle(CurrentHandle);

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

EXTERN_C HRESULT WINAPI MoManageCompactOS(
    _In_ PNSUDO_CONTEXT Context)
{
    Mile::HResult hr = S_OK;
    HANDLE PreviousContextTokenHandle = INVALID_HANDLE_VALUE;

    do
    {
        if (!::IsWindows10OrGreater())
        {
            hr = E_NOINTERFACE;
            break;
        }

        DWORD PurgeMode = ::MoPrivateParsePurgeMode(Context);
        if (PurgeMode == 0)
        {
            hr = Mile::HResult::FromWin32(ERROR_CANCELLED);
            break;
        }

        if (PurgeMode != MO_PRIVATE_PURGE_MODE_QUERY &&
            PurgeMode != MO_PRIVATE_PURGE_MODE_ENABLE &&
            PurgeMode != MO_PRIVATE_PURGE_MODE_DISABLE)
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

        if (PurgeMode == MO_PRIVATE_PURGE_MODE_QUERY)
        {
            DWORD DeploymentState = 0;
            ::MoPrivateWriteLine(
                Context,
                L"CompactOS is %s.",
                (Mile::GetCompactOsDeploymentState(
                    &DeploymentState).IsSucceeded()
                    && DeploymentState != FALSE)
                ? L"Enabled"
                : L"Disabled");
        }
        else if (PurgeMode == MO_PRIVATE_PURGE_MODE_ENABLE)
        {
            hr = Mile::SetCompactOsDeploymentState(TRUE);
            if (hr.IsFailed())
            {
                ::MoPrivateWriteErrorMessage(
                    Context,
                    hr,
                    L"Mile::SetCompactOsDeploymentState");
                break;
            }

            ::CompressFileWorker(
                Context,
                Mile::ExpandEnvironmentStringsW(L"%SystemDrive%\\").c_str());
        }
        else if (PurgeMode == MO_PRIVATE_PURGE_MODE_DISABLE)
        {
            ::UncompressFileWorker(
                Context,
                Mile::ExpandEnvironmentStringsW(L"%SystemDrive%\\").c_str());

            DWORD DeploymentState = 0;
            if (Mile::GetCompactOsDeploymentState(
                &DeploymentState).IsSucceeded()
                && DeploymentState != FALSE)
            {
                hr = Mile::SetCompactOsDeploymentState(FALSE);
                if (hr.IsFailed())
                {
                    ::MoPrivateWriteErrorMessage(
                        Context,
                        hr,
                        L"Mile::SetCompactOsDeploymentState");
                    break;
                }
            }
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
