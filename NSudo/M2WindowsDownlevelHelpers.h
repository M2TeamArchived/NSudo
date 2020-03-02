/*
 * PROJECT:   M2-Team Common Library
 * FILE:      M2WindowsDownlevelHelpers.h
 * PURPOSE:   Definition for the Windows downlevel helper functions
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#pragma once

#ifndef _M2_WINDOWS_DOWNLEVEL_HELPERS_
#define _M2_WINDOWS_DOWNLEVEL_HELPERS_

#include <Mile.Windows.h>

/**
 * Retrieves the calling thread's last-error code value. The last-error code is
 * maintained on a per-thread basis. Multiple threads do not overwrite each
 * other's last-error code.
 *
 * @param IsLastFunctionCallSucceeded Set this parameter TRUE if you can be
 *                                    sure that the last call was succeeded.
 *                                    Otherwise, set this parameter FALSE.
 * @param UseLastErrorWhenSucceeded Set this parameter TRUE if you want to use
 *                                  last-error code if the last call was
 *                                  succeeded. Otherwise, set this parameter
 *                                  FALSE.
 * @return The calling thread's last-error code.
 */
DWORD M2GetLastWin32Error(
    _In_ BOOL IsLastFunctionCallSucceeded = FALSE,
    _In_ BOOL UseLastErrorWhenSucceeded = FALSE);

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
HRESULT M2GetLastHResultError(
    _In_ BOOL IsLastFunctionCallSucceeded = FALSE,
    _In_ BOOL UseLastErrorWhenSucceeded = FALSE);

/**
 * Creates a single uninitialized object of the class associated with a
 * specified CLSID.
 *
 * @param lpszCLSID The string representation of the CLSID.
 * @param pUnkOuter If NULL, indicates that the object is not being created as
 *                  part of an aggregate. If non-NULL, pointer to the aggregate
 *                  object's IUnknown interface (the controlling IUnknown).
 * @param dwClsContext Context in which the code that manages the newly created
 *                     object will run. The values are taken from the
 *                     enumeration CLSCTX.
 * @param lpszIID A pointer to the string representation of the IID.
 * @param ppv Address of pointer variable that receives the interface pointer
 *            requested in riid. Upon successful return, *ppv contains the
 *            requested interface pointer. Upon failure, *ppv contains NULL.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see CoCreateInstance.
 */
HRESULT M2CoCreateInstance(
    _In_ LPCWSTR lpszCLSID,
    _In_opt_ LPUNKNOWN pUnkOuter,
    _In_ DWORD dwClsContext,
    _In_ LPCWSTR lpszIID,
    _Out_ LPVOID* ppv);

#endif // !_M2_WINDOWS_DOWNLEVEL_HELPERS_
