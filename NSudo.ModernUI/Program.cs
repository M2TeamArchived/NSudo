using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NSudo.ModernUI
{
    public class Program
    {
        [STAThread()]
        public static int ModernUIEntry(string Arguments)
        {
            System.Windows.Application App = new System.Windows.Application();
            App.StartupUri = new Uri("/NSudo.ModernUI;component/mainwindow.xaml", UriKind.Relative);
            return App.Run();
        }

        [STAThread()]
        public static void Main()
        {
            ModernUIEntry(null);
        }
    }
}
