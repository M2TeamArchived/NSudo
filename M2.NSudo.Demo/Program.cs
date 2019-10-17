using System;

namespace M2.NSudo.Demo
{
    class Program
    {
        static void Main(string[] args)
        {
            NSudoInstance instance = new NSudoInstance();

            INSudoClient client = instance.CreateClient();

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
