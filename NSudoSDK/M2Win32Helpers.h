/*
 * PROJECT:   M2-Team Common Library
 * FILE:      M2Win32Helpers.h
 * PURPOSE:   Definition for the Win32 desktop helper functions
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#pragma once

#ifndef _M2_WIN32_HELPERS_
#define _M2_WIN32_HELPERS_

#include "M2BaseHelpers.h"

/**
 * The resource info struct.
 */
typedef struct _M2_RESOURCE_INFO
{
    DWORD Size;
    LPVOID Pointer;
} M2_RESOURCE_INFO, *PM2_RESOURCE_INFO;

/**
 * Obtain the best matching resource with the specified type and name in the
 * specified module.
 *
 * @param lpResourceInfo The resource info which contains the pointer and size.
 * @param hModule A handle to the module whose portable executable file or an
 *                accompanying MUI file contains the resource. If this
 *                parameter is NULL, the function searches the module used to
 *                create the current process.
 * @param lpType The resource type. Alternately, rather than a pointer, this
 *               parameter can be MAKEINTRESOURCE(ID), where ID is the integer
 *               identifier of the given resource type.
 * @param lpName The name of the resource. Alternately, rather than a pointer,
 *               this parameter can be MAKEINTRESOURCE(ID), where ID is the
 *               integer identifier of the resource.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2LoadResource(
    _Out_ PM2_RESOURCE_INFO lpResourceInfo,
    _In_opt_ HMODULE hModule,
    _In_ LPCWSTR lpType,
    _In_ LPCWSTR lpName);

namespace M2
{
    /**
     * The handle definer for SC_HANDLE object.
     */
#pragma region CServiceHandle

    struct CServiceHandleDefiner
    {
        static inline SC_HANDLE GetInvalidValue()
        {
            return nullptr;
        }

        static inline void Close(SC_HANDLE Object)
        {
            CloseServiceHandle(Object);
        }
    };

    typedef CObject<SC_HANDLE, CServiceHandleDefiner> CServiceHandle;

#pragma endregion

    /**
     * The handle definer for PSID object.
     */
#pragma region CSID

    struct CSIDDefiner
    {
        static inline PSID GetInvalidValue()
        {
            return nullptr;
        }

        static inline void Close(PSID Object)
        {
            FreeSid(Object);
        }
    };

    typedef CObject<PSID, CSIDDefiner> CSID;

#pragma endregion

    /**
     * The handle definer for memory block allocated via WTS API.
     */
#pragma region CWTSMemory

    template<typename TMemoryBlock>
    struct CWTSMemoryDefiner
    {
        static inline TMemoryBlock GetInvalidValue()
        {
            return nullptr;
        }

        static inline void Close(TMemoryBlock Object)
        {
            WTSFreeMemory(Object);
        }
    };

    template<typename TMemoryBlock>
    class CWTSMemory :
        public CObject<TMemoryBlock, CWTSMemoryDefiner<TMemoryBlock>>
    {

    };

#pragma endregion

    /**
     * The handle definer for HKEY object.
     */
#pragma region CHKey

    struct CHKeyDefiner
    {
        static inline HKEY GetInvalidValue()
        {
            return nullptr;
        }

        static inline void Close(HKEY Object)
        {
            RegCloseKey(Object);
        }
    };

    typedef CObject<HKEY, CHKeyDefiner> CHKey;

#pragma endregion

}

/**
 * Retrieves the path of the shared Windows directory on a multi-user system.
 *
 * @param WindowsFolderPath The string of the path of the shared Windows
 *                          directory on a multi-user system.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2GetWindowsDirectory(
    std::wstring& WindowsFolderPath);

/**
 * Starts a service if not started and retrieves the current status of the
 * specified service.
 *
 * @param lpServiceName The name of the service to be started. This is the name
 *                      specified by the lpServiceName parameter of the
 *                      CreateService function when the service object was
 *                      created, not the service display name that is shown by
 *                      user interface applications to identify the service.
 *                      The maximum string length is 256 characters. The
 *                      service control manager database preserves the case of
 *                      the characters, but service name comparisons are always
 *                      case insensitive. Forward-slash (/) and backslash ()
 *                      are invalid service name characters.
 * @param lpServiceStatus Contains process status information for a service.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2StartService(
    _In_ LPCWSTR lpServiceName,
    _Out_ LPSERVICE_STATUS_PROCESS lpServiceStatus);

/**
 * Loads the specified module with the optimization of the mitigation of DLL
 * preloading attacks into the address space of the calling process safely. The
 * specified module may cause other modules to be loaded.
 *
 * @param ModuleHandle If the function succeeds, this parameter's value is a
 *                     handle to the loaded module. You should read the
 *                     documentation about LoadLibraryEx API for further
 *                     information.
 * @param LibraryFileName A string that specifies the file name of the module
 *                        to load. You should read the documentation about
 *                        LoadLibraryEx API for further information.
 * @param Flags The action to be taken when loading the module. You should read
 *              the documentation about LoadLibraryEx API for further
 *              information.
 * @return HRESULT.
 */
HRESULT M2LoadLibraryEx(
    _Out_ HMODULE& ModuleHandle,
    _In_ LPCWSTR LibraryFileName,
    _In_ DWORD Flags);

/**
 * Determines whether the interface id have the correct interface name.
 *
 * @param InterfaceID A pointer to the string representation of the IID.
 * @param InterfaceName A pointer to the interface name string.
 * @return HRESULT. If the function succeeds, the return value is S_OK.
 */
HRESULT M2CoCheckInterfaceName(
    _In_ LPCWSTR InterfaceID,
    _In_ LPCWSTR InterfaceName);

#endif // _M2_WIN32_HELPERS_
