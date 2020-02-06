/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.h
 * PURPOSE:   Mouri Internal Library Essentials Definition for Windows
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef MILE_WINDOWS
#define MILE_WINDOWS

#ifndef __cplusplus
#error "[Mile.Windows] You should use a C++ compiler."
#endif // !__cplusplus

#include "Mile.Windows.Platform.h"

/**
 * Allocates a block of memory from the default heap of the calling process.
 * The allocated memory will be initialized to zero. The allocated memory is
 * not movable.
 *
 * @param Size The number of bytes to be allocated.
 * @param Block A pointer to the allocated memory block.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI MileAllocMemory(
    _In_ SIZE_T Size,
    _Out_ LPVOID* Block);

/**
 * Reallocates a block of memory from the default heap of the calling process.
 * If the reallocation request is for a larger size, the additional region of
 * memory beyond the original size be initialized to zero. This function
 * enables you to resize a memory block and change other memory block
 * properties. The allocated memory is not movable.
 *
 * @param OldBlock A pointer to the block of memory that the function
 *                 reallocates. This pointer is returned by an earlier call to
 *                 the MileAllocMemory or MileReAllocMemory function.
 * @param NewSize The new size of the memory block, in bytes. A memory block's
 *                size can be increased or decreased by using this function.
 * @param NewBlock A pointer to the allocated memory block.
 * @return HRESULT. If the function succeeds, the return value is S_OK. If the
 *         function fails, the original memory is not freed, and the original
 *         handle and pointer are still valid.
 */
EXTERN_C HRESULT WINAPI MileReAllocMemory(
    _In_ PVOID OldBlock,
    _In_ SIZE_T NewSize,
    _Out_ LPVOID* NewBlock);

/**
 * Frees a memory block allocated from a heap by the MileAllocMemory or
 * MileReAllocMemory function.
 *
 * @param Block A pointer to the memory block to be freed. This pointer is
 *              returned by the AllocMemory or ReAllocMemory function. If this
 *              pointer is nullptr, the behavior is undefined.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI MileFreeMemory(
    _In_ LPVOID Block);

/**
 * Retrieves a specified type of information about an access token. The calling
 * process must have appropriate access rights to obtain the information.
 *
 * @param TokenHandle A handle to an access token from which information is
 *                    retrieved.
 * @param TokenInformationClass Specifies a value from the
 *                              TOKEN_INFORMATION_CLASS enumerated type to
 *                              identify the type of information the function
 *                              retrieves.
 * @param OutputInformation A pointer to a buffer the function fills with the
 *                          requested information. When you have finished using
 *                          the information, free it by calling the
 *                          MileFreeMemory function. You should also set the
 *                          pointer to nullptr.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see GetTokenInformation.
 */
EXTERN_C HRESULT WINAPI MileGetTokenInformationWithMemory(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _Out_ PVOID* OutputInformation);

/**
 * Enables or disables privileges in the specified access token.
 *
 * @param TokenHandle A handle to the access token that contains the privileges
 *                    to be modified. The handle must have
 *                    TOKEN_ADJUST_PRIVILEGES access to the token.
 * @param Privileges A pointer to an array of LUID_AND_ATTRIBUTES structures
 *                   that specifies an array of privileges and their
 *                   attributes. Each structure contains the LUID and
 *                   attributes of a privilege. To get the name of the
 *                   privilege associated with a LUID, call the
 *                   MileGetPrivilegeValue function, passing the address of the
 *                   LUID as the value of the lpLuid parameter. The attributes
 *                   of a privilege can be a combination of the following
 *                   values.
 *                   SE_PRIVILEGE_ENABLED
 *                       The function enables the privilege.
 *                   SE_PRIVILEGE_REMOVED
 *                       The privilege is removed from the list of privileges
 *                       in the token.
 *                   None
 *                       The function disables the privilege.
 * @param PrivilegeCount The number of entries in the Privileges array.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see AdjustTokenPrivileges.
 */
EXTERN_C HRESULT WINAPI MileAdjustTokenPrivilegesSimple(
    _In_ HANDLE TokenHandle,
    _In_ PLUID_AND_ATTRIBUTES Privileges,
    _In_ DWORD PrivilegeCount);

/**
 * Enables or disables all privileges in the specified access token.
 *
 * @param TokenHandle A handle to the access token that contains the privileges
 *                    to be modified. The handle must have
 *                    TOKEN_ADJUST_PRIVILEGES access to the token.
 * @param Attributes The attributes of all privileges can be a combination of
 *                   the following values.
 *                   SE_PRIVILEGE_ENABLED
 *                       The function enables the privilege.
 *                   SE_PRIVILEGE_REMOVED
 *                       The privilege is removed from the list of privileges
 *                       in the token.
 *                   None
 *                       The function disables the privilege.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI MileAdjustTokenAllPrivileges(
    _In_ HANDLE TokenHandle,
    _In_ DWORD Attributes);

#endif // !MILE_WINDOWS
