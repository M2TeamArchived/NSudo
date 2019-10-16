using System;
using System.Collections.Generic;
using System.Reflection;
using System.Runtime.InteropServices;

namespace M2.NSudo
{
    public class NSudoInstance
    {

        /// <summary>
        /// Creates an interface object and returns a pointer to it.
        /// </summary>
        /// <param name="InterfaceId">
        /// The Interface ID being requested.
        /// </param>
        /// <returns>
        /// A location to store the interface pointer to return.
        /// </returns>
        [DllImport("NSudoAPI.dll",CallingConvention = CallingConvention.Winapi, CharSet = CharSet.Unicode, ExactSpelling =true, PreserveSig =false)]
        [return: MarshalAs(UnmanagedType.Interface)]
        private static extern object NSudoCreateInstance(
            [MarshalAs(UnmanagedType.LPStruct)] Guid InterfaceId);
        // UnmanagedFunctionPointer

        public static object Create(/*Dictionary<Architecture, string> BinaryPaths*/)
        {
            //if (BinaryPaths.Count == 0)
            //{
            //    BinaryPaths[Architecture.X86] = "F:\\GitHub\\M2Team\\NSudo\\Output\\Release\\Win32\\NSudoAPI.dll";
            //    BinaryPaths[Architecture.X64] = "F:\\GitHub\\M2Team\\NSudo\\Output\\Release\\x64\\NSudoAPI.dll";
            //    BinaryPaths[Architecture.Arm] = "F:\\GitHub\\M2Team\\NSudo\\Output\\Release\\ARM\\NSudoAPI.dll";
            //    BinaryPaths[Architecture.Arm64] = "F:\\GitHub\\M2Team\\NSudo\\Output\\Release\\ARM64\\NSudoAPI.dll";
            //}

            //BinaryPaths[RuntimeInformation.ProcessArchitecture] = "";

            return NSudoCreateInstance(
                new Guid("8BD99D5D-2811-4036-A21E-63328115B364"));
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            INSudoClient client = (INSudoClient)NSudoInstance.Create();

            IntPtr currentProcessToken = client.OpenCurrentProcessToken(0x02000000);
            if (currentProcessToken != null)
            {
                client.AdjustTokenAllPrivileges(currentProcessToken, 0x00000002);
            }

            Console.WriteLine("Hello World!");

            Console.ReadKey();
        }
    }
}
