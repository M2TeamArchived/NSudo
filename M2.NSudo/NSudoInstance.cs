using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.InteropServices;

namespace M2.NSudo
{
    /// <summary>
    /// The utility class help you to load NSudo Shared Library.
    /// </summary>
    public class NSudoInstance
    {
        /// <summary>
        /// Creates an interface object and returns a pointer to it.
        /// </summary>
        /// <param name="InterfaceId">
        /// The Interface ID being requested.
        /// </param>
        /// <param name="Instance">
        /// A location to store the interface pointer to return.
        /// </param>
        /// <returns>
        /// HRESULT. If the function succeeds, the return value is S_OK.
        /// </returns>
        [UnmanagedFunctionPointer(CallingConvention.Winapi, CharSet = CharSet.Unicode)]
        private delegate int NSudoCreateInstanceType(
            [MarshalAs(UnmanagedType.LPStruct)] Guid InterfaceId,
            [MarshalAs(UnmanagedType.Interface)] out object Instance);

        private IntPtr ModuleHandle;

        /// <summary>
        /// Initialize the NSudoInstance.
        /// </summary>
        /// <param name="BinaryPaths">
        /// Help you customize the path of NSudo Shared Library.
        /// </param>
        public NSudoInstance(Dictionary<Architecture, string> BinaryPaths)
        {
            string BaseDirectory = AppDomain.CurrentDomain.BaseDirectory;

            if (BinaryPaths.Count == 0)
            {
                BinaryPaths.TryAdd(
                    Architecture.X86, 
                    BaseDirectory + "Win32\\NSudoAPI.dll");
                BinaryPaths.TryAdd(
                    Architecture.X64,
                    BaseDirectory + "x64\\NSudoAPI.dll");
                BinaryPaths.TryAdd(
                    Architecture.Arm,
                    BaseDirectory + "ARM\\NSudoAPI.dll");
                BinaryPaths.TryAdd(
                    Architecture.Arm64,
                    BaseDirectory + "ARM64\\NSudoAPI.dll");
            }

            this.ModuleHandle = Win32.LoadLibrary(
                BinaryPaths[RuntimeInformation.ProcessArchitecture]);
            if (this.ModuleHandle == IntPtr.Zero)
            {
                throw new Win32Exception(Marshal.GetLastWin32Error());
            }
        }

        /// <summary>
        /// Initialize the NSudoInstance.
        /// </summary>
        public NSudoInstance() :
            this(new Dictionary<Architecture, string>())
        {
        }

        /// <summary>
        /// Uninitialize the NSudoInstance.
        /// </summary>
        ~NSudoInstance()
        {
            if (!Win32.FreeLibrary(this.ModuleHandle))
            {
                throw new Win32Exception(Marshal.GetLastWin32Error());
            }
        }

        /// <summary>
        /// Creates an interface object.
        /// </summary>
        /// <param name="InterfaceId">
        /// The Interface ID being requested.
        /// </param>
        /// <returns>
        /// A interface object to return.
        /// </returns>
        public object CreateInstance(Guid InterfaceId)
        {
            IntPtr NSudoCreateInstanceAddress = Win32.GetProcAddress(
                this.ModuleHandle, "NSudoCreateInstance");
            if (NSudoCreateInstanceAddress == IntPtr.Zero)
            {
                throw new Win32Exception(Marshal.GetLastWin32Error());
            }

            NSudoCreateInstanceType NSudoCreateInstance =
                Marshal.GetDelegateForFunctionPointer<NSudoCreateInstanceType>(
                    NSudoCreateInstanceAddress);

            object Instance;
            int hr = NSudoCreateInstance(InterfaceId, out Instance);
            if (hr != 0)
            {
                throw new ExternalException("-", hr);
            }

            return Instance;
        }

        /// <summary>
        /// Creates an INSudoClient interface object.
        /// </summary>
        /// <returns>
        /// An INSudoClient interface object to return.
        /// </returns>
        public INSudoClient CreateClient()
        {
            return (INSudoClient)this.CreateInstance(
                new Guid("8BD99D5D-2811-4036-A21E-63328115B364"));
        }
    }
}
