/*
 * PROJECT:   NSudo Sweeper
 * FILE:      NSudoSweeperCore.cpp
 * PURPOSE:   NSudo Sweeper Core Implementation for Windows
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef __cplusplus
#error "[Mile.Windows] You should use a C++ compiler."
#endif // !__cplusplus

#include "NSudoSweeperCore.h"

#include <wchar.h>

/**
 * @remark You can read the definition for this function in
 *         "NSudoSweeperCore.h".
 */
BOOL WINAPI NSudoSweeperIsOnlineImage(
    _In_ LPCWSTR SessionRootPath)
{
    UNREFERENCED_PARAMETER(SessionRootPath);

    if (SessionRootPath)
    {
        return TRUE;
    }

    wchar_t Buffer[32768];
    const UINT BufferSize = sizeof(Buffer) / sizeof(*Buffer);

    if (::GetSystemDirectoryW(Buffer, BufferSize))
    {
        ::wcschr(Buffer, '\\')[1] = '\0';

        return (::_wcsicmp(SessionRootPath, Buffer) == 0);
    }

    return FALSE;
}

/**
 * @remark You can read the definition for this function in
 *         "NSudoSweeperCore.h".
 */
EXTERN_C HRESULT WINAPI NSudoSweeperSystemRestorePointCleanupHandler(
    _In_ LPCWSTR Configuration,
    _In_opt_ LPCWSTR SessionRootPath,
    _Out_opt_ PUINT64 EstimatedFreedSize,
    _In_opt_ NSudoSweeperCallback Callback,
    _In_opt_ LPVOID UserData)
{
    if (!Configuration)
    {
        return E_INVALIDARG;
    }

    if (!::NSudoSweeperIsOnlineImage(SessionRootPath))
    {
        return E_NOTIMPL;
    }

    if (EstimatedFreedSize)
    {
        *EstimatedFreedSize = 0;
    }
    else
    {
        DWORD Progress = 0;

        if (Callback)
        {
            Callback(NSUDO_SWEEPER_PROGRESS_MESSAGE, &Progress, UserData);
        }

        ::MessageBoxW(nullptr, L"Start cleaning", L"Test", 0);
    }

    return S_OK;
}
