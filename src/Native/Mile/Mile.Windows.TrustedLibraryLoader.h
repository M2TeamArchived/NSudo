/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.TrustedLibraryLoader.h
 * PURPOSE:   Trusted Library Loader Definition for Windows
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef MILE_WINDOWS_TRUSTED_LIBRARY_LOADER
#define MILE_WINDOWS_TRUSTED_LIBRARY_LOADER

#include <Windows.h>

/**
 * @brief Loads the specified module in the system directory into the address
 *        space of the calling process. The specified module may cause other
 *        modules to be loaded.
 * @param lpLibFileName The name of the module. This can be either a library
 *                      module (a .dll file) or an executable module (an .exe
 *                      file). The name specified is the file name of the
 *                      module and is not related to the name stored in the
 *                      library module itself, as specified by the LIBRARY
 *                      keyword in the module-definition (.def) file.
 *                      If the string specifies a full path, the function
 *                      searches only that path for the module.
 *                      If the string specifies a relative path or a module
 *                      name without a path, the function uses a standard
 *                      search strategy to find the module.
 *                      If the function cannot find the module, the function
 *                      fails. When specifying a path, be sure to use
 *                      backslashes (\), not forward slashes (/).
 *                      If the string specifies a module name without a path
 *                      and the file name extension is omitted, the function
 *                      appends the default library extension .dll to the
 *                      module name. To prevent the function from appending
 *                      .dll to the module name, include a trailing point
 *                      character (.) in the module name string.
 * @return If the function succeeds, the return value is a handle to the
 *         module. If the function fails, the return value is nullptr. To get
 *         extended error information, call GetLastError.
 * @remark For more information, see LoadLibrary and LoadLibraryEx.
 */
EXTERN_C HMODULE WINAPI MileLoadLibraryFromSystem32(
    _In_ LPCWSTR lpLibFileName);

#endif // !MILE_WINDOWS_TRUSTED_LIBRARY_LOADER
