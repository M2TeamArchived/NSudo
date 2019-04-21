/*
 * PROJECT:   M2-Team Common Library
 * FILE:      M2WindowsBaseHelpers.cpp
 * PURPOSE:   Implementation for the basic Windows helper functions
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "stdafx.h"

#include "M2WindowsBaseHelpers.h"

/**
 * Retrieves the calling thread's last-error code value. The last-error code is
 * maintained on a per-thread basis. Multiple threads do not overwrite each
 * other's last-error code.
 *
 * @param KnownFailed Set this parameter TRUE if you can be sure that the last
 *                    call was failed, Otherwise, set this parameter FALSE.
 * @param LastErrorCode A pointer to a variable that returns the calling
 *                      thread's last-error code. This parameter can be NULL.
 * @return The calling thread's last-error code which is converted to an
 *         HRESULT value.
 */
HRESULT M2GetLastError(
    _In_ BOOL KnownFailed,
    _Out_opt_ PDWORD LastErrorCode)
{
    DWORD LastError = GetLastError();

    if (KnownFailed && ERROR_SUCCESS == LastError)
        LastError = ERROR_FUNCTION_FAILED;

    if (LastErrorCode)
        *LastErrorCode = LastError;

    return HRESULT_FROM_WIN32(LastError);
}
