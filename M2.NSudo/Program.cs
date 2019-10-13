using System;
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
        [
            DllImport(
                "NSudoAPI.dll",
                CharSet = CharSet.Unicode,
                ExactSpelling = true)
        ]
        
        private static extern int NSudoCreateInstance(
            [MarshalAs(UnmanagedType.LPStruct)] Guid InterfaceId,
            [MarshalAs(UnmanagedType.Interface)] out object Instance);

        public static object Create()
        {
            object Instance;
            int hr = NSudoCreateInstance(
                new Guid("8BD99D5D-2811-4036-A21E-63328115B364"), out Instance);
            if (hr != 0)
            {
                throw new ExternalException("-", hr);
            }
            return Instance;
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
