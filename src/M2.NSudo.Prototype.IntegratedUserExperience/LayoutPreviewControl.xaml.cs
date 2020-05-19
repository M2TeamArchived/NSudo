using System;
using System.Collections.Generic;
using System.Drawing.Printing;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace M2.NSudo.Prototype.IntegratedUserExperience
{
    /// <summary>
    /// LayoutPreviewControl.xaml 的交互逻辑
    /// </summary>
    public partial class LayoutPreviewControl : UserControl
    {
        public LayoutPreviewControl()
        {
            InitializeComponent();
        }

        private void LayoutPreviewControlInternal_LayoutUpdated(object sender, EventArgs e)
        {
            try
            {
                FrameworkElement ParentWindow = (FrameworkElement)Window.GetWindow(this).Content;

                Point CurrentPoint = TransformToAncestor(ParentWindow).Transform(new Point(0, 0));

                Thickness LayoutValue = new Thickness(
                    CurrentPoint.X,
                    CurrentPoint.Y,
                    ParentWindow.ActualWidth - CurrentPoint.X - ActualWidth,
                    ParentWindow.ActualHeight - CurrentPoint.Y - ActualHeight);

                MarginText.Text = LayoutValue.ToString();
            }
            catch (Exception)
            {
                
            }
        }
    }
}
