using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
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
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show(
                "NSudo.WPF load by NSudo.Win32",
                "NSudo",
                MessageBoxButton.OK,
                MessageBoxImage.Information);
        }

        [DllImport("NSudo.exe")]
        private static extern void Test();


        private void btnRun_Click(object sender, RoutedEventArgs e)
        {
            Test();

            MessageBox.Show(
                System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName,
                "NSudo",
                MessageBoxButton.OK,
                MessageBoxImage.Information);
        }
    }
}
