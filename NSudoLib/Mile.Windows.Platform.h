/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.Platform.h
 * PURPOSE:   Mouri Internal Library Essentials Base Definition for Windows
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef MILE_WINDOWS_PLATFORM
#define MILE_WINDOWS_PLATFORM

#ifndef __cplusplus
#error "[Mile.Windows.Platform] You should use a C++ compiler."
#endif // !__cplusplus

#include <Windows.h>

/**
 * Retrieves a handle to the default heap of the calling process. This handle
 * can then be used in subsequent calls to the heap functions.
 *
 * @return The handle to the calling process's heap.
 * @remark For more information, see GetProcessHeap.
 */
EXTERN_C HANDLE WINAPI MileGetProcessHeap();

/**
 * Allocates a block of memory from a heap. The allocated memory is not
 * movable.
 *
 * @param hHeap A handle to the heap from which the memory will be allocated.
 * @param dwFlags The heap allocation options.
 * @param dwBytes The number of bytes to be allocated.
 * @param lpNewMem A pointer to the allocated memory block.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see HeapAlloc.
 */
EXTERN_C HRESULT WINAPI MileHeapAlloc(
    _In_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ SIZE_T dwBytes,
    _Out_ LPVOID* lpNewMem);

/**
 * Reallocates a block of memory from a heap. This function enables you to
 * resize a memory block and change other memory block properties. The
 * allocated memory is not movable.
 *
 * @param hHeap A handle to the heap from which the memory is to be
 *              reallocated.
 * @param dwFlags The heap reallocation options.
 * @param lpMem A pointer to the block of memory that the function reallocates.
 *              This pointer is returned by an earlier call to the
 *              MileHeapAlloc or MileHeapReAlloc function.
 * @param dwBytes The new size of the memory block, in bytes. A memory block's
 *                size can be increased or decreased by using this function.
 * @param lpNewMem A pointer to the allocated memory block.
 * @return HRESULT. If the function succeeds, the return value is S_OK. If the
 *         function fails, the original memory is not freed, and the original
 *         handle and pointer are still valid.
 * @remark For more information, see HeapReAlloc.
 */
EXTERN_C HRESULT WINAPI MileHeapReAlloc(
    _Inout_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ LPVOID lpMem,
    _In_ SIZE_T dwBytes,
    _Out_ LPVOID* lpNewMem);

/**
 * Frees a memory block allocated from a heap by the MileHeapAlloc or
 * MileHeapReAlloc function.
 *
 * @param hHeap A handle to the heap whose memory block is to be freed.
 * @param dwFlags The heap free options.
 * @param lpMem A pointer to the memory block to be freed.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see HeapFree.
 */
EXTERN_C HRESULT WINAPI MileHeapFree(
    _Inout_ HANDLE hHeap,
    _In_ DWORD dwFlags,
    _In_ LPVOID lpMem);

/**
 * Enables or disables privileges in the specified access token. Enabling or
 * disabling privileges in an access token requires TOKEN_ADJUST_PRIVILEGES
 * access.
 *
 * @param TokenHandle A handle to the access token that contains the privileges
 *                    to be modified. The handle must have
 *                    TOKEN_ADJUST_PRIVILEGES access to the token. If the
 *                    PreviousState parameter is not NULL, the handle must also
 *                    have TOKEN_QUERY access.
 * @param DisableAllPrivileges Specifies whether the function disables all of
 *                             the token's privileges. If this value is TRUE,
 *                             the function disables all privileges and ignores
 *                             the NewState parameter. If it is FALSE, the
 *                             function modifies privileges based on the
 *                             information pointed to by the NewState
 *                             parameter.
 * @param NewState A pointer to a TOKEN_PRIVILEGES structure that specifies an
 *                 array of privileges and their attributes. If
 *                 DisableAllPrivileges is TRUE, the function ignores this
 *                 parameter.
 * @param BufferLength Specifies the size, in bytes, of the buffer pointed to
 *                     by the PreviousState parameter. This parameter can be
 *                     zero if the PreviousState parameter is NULL.
 * @param PreviousState A pointer to a buffer that the function fills with a
 *                      TOKEN_PRIVILEGES structure that contains the previous
 *                      state of any privileges that the function modifies.
 *                      This parameter can be NULL.
 * @param ReturnLength A pointer to a variable that receives the required size,
 *                     in bytes, of the buffer pointed to by the PreviousState
 *                     parameter. This parameter can be NULL if PreviousState
 *                     is NULL.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 * @remark For more information, see AdjustTokenPrivileges.
 */
EXTERN_C HRESULT WINAPI MileAdjustTokenPrivileges(
    _In_ HANDLE TokenHandle,
    _In_ BOOL DisableAllPrivileges,
    _In_opt_ PTOKEN_PRIVILEGES NewState,
    _In_ DWORD BufferLength,
    _Out_opt_ PTOKEN_PRIVILEGES PreviousState,
    _Out_opt_ PDWORD ReturnLength);

/**
 * Retrieves a specified type of information about an access token. The calling
 * process must have appropriate access rights to obtain the information.
 *
 * @param TokenHandle A handle to an access token from which information is
 *                    retrieved.
 * @param TokenInformationClass Specifies a value from the
 *                              TOKEN_INFORMATION_CLASS enumerated type to
 *                              identify the type of information the
 *                              function retrieves.
 * @param TokenInformation A pointer to a buffer the function fills with the
 *                         requested information.
 * @param TokenInformationLength Specifies the size, in bytes, of the buffer
 *                               pointed to by the TokenInformation parameter.
 * @param ReturnLength A pointer to a variable that receives the number of
 *                     bytes needed for the buffer pointed to by the
 *                     TokenInformation parameter.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see GetTokenInformation.
 */
EXTERN_C HRESULT WINAPI MileGetTokenInformation(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _Out_opt_ LPVOID TokenInformation,
    _In_ DWORD TokenInformationLength,
    _Out_ PDWORD ReturnLength);

/**
 * Sets various types of information for a specified access token. The
 * information that this function sets replaces existing information. The
 * calling process must have appropriate access rights to set the information.
 *
 * @param TokenHandle A handle to the access token for which information is to
 *                    be set.
 * @param TokenInformationClass A value from the TOKEN_INFORMATION_CLASS
 *                              enumerated type that identifies the type of
 *                              information the function sets. The valid values
 *                              from TOKEN_INFORMATION_CLASS are described in
 *                              the TokenInformation parameter.
 * @param TokenInformation A pointer to a buffer that contains the information
 *                         set in the access token.
 * @param TokenInformationLength Specifies the length, in bytes, of the buffer
 *                               pointed to by TokenInformation.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see SetTokenInformation.
 */
EXTERN_C HRESULT WINAPI MileSetTokenInformation(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _In_ LPVOID TokenInformation,
    _In_ DWORD TokenInformationLength);

/**
 * Retrieves the locally unique identifier (LUID) used on the local system to
 * locally represent the specified privilege name.
 *
 * @param Name A pointer to a null-terminated string that specifies the name of
 *             the privilege, as defined in the Winnt.h header file. For
 *             example, this parameter could specify the constant,
 *             SE_SECURITY_NAME, or its corresponding string,
 *             "SeSecurityPrivilege".
 * @param Value A pointer to a variable that receives the LUID by which the
 *              privilege is known on the local system.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 * @remark For more information, see LookupPrivilegeValue.
 */
EXTERN_C HRESULT WINAPI MileGetPrivilegeValue(
    _In_ LPCWSTR Name,
    _Out_ PLUID Value);

/**
 * Starts a service if not started and retrieves the current status of the
 * specified service.
 *
 * @param ServiceName The name of the service to be started. This is the name
 *                    specified by the ServiceName parameter of the
 *                    CreateService function when the service object was
 *                    created, not the service display name that is shown by
 *                    user interface applications to identify the service. The
 *                    maximum string length is 256 characters. The service
 *                    control manager database preserves the case of the
 *                    characters, but service name comparisons are always case
 *                    insensitive. Forward-slash (/) and backslash (\) are
 *                    invalid service name characters.
 * @param ServiceStatus A pointer to the process status information for a
 *                      service.
 * @return HRESULT. If the method succeeds, the return value is S_OK.
 */
EXTERN_C HRESULT WINAPI MileStartService(
    _In_ LPCWSTR ServiceName,
    _Out_ LPSERVICE_STATUS_PROCESS ServiceStatus);

/**
 * Retrieves the number of milliseconds that have elapsed since the system was
 * started.
 *
 * @return The number of milliseconds.
 */
EXTERN_C ULONGLONG WINAPI MileGetTickCount();

#endif // !MILE_WINDOWS_PLATFORM
