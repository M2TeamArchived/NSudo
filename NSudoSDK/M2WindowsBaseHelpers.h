/*
 * PROJECT:   M2-Team Common Library
 * FILE:      M2WindowsBaseHelpers.h
 * PURPOSE:   Definition for the basic Windows helper functions
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#pragma once

#ifndef _M2_WINDOWS_BASE_HELPERS_
#define _M2_WINDOWS_BASE_HELPERS_

#include <Windows.h>

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
    _Out_opt_ PDWORD LastErrorCode);

#endif // _M2_WINDOWS_BASE_HELPERS_
