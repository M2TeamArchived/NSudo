using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace NSudo.ModernUI
{
    /// <summary>
    /// InfoPage.xaml 的交互逻辑
    /// </summary>
    public partial class InfoPage : Page
    {
        public InfoPage()
        {
            InitializeComponent();
        }

        private void Hyperlink_RequestNavigate(object sender, RequestNavigateEventArgs e)
        {
            try
            {
                Process.Start(new ProcessStartInfo(e.Uri.AbsoluteUri));
            }
            catch (Exception) { }

            e.Handled = true;
        }

        private void NSudoOpenOfficalQQGroupEvent(object sender, MouseButtonEventArgs e)
        {
            try
            {
                Process.Start(new ProcessStartInfo("http://shang.qq.com/wpa/qunwpa?idkey=29940ed5c8b2363efcf8a1c376f280c4a46c4e356d5533af48541418ff13ada2"));
            }
            catch (Exception) { }
        }

        private void NSudoOpenProjectWebSiteEvent(object sender, MouseButtonEventArgs e)
        {
            try
            {
                Process.Start(new ProcessStartInfo("https://github.com/M2Team/NSudo"));
            }
            catch (Exception) { }
        }
    }
}
