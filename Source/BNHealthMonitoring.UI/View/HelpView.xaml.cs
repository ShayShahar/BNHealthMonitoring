using System;
using System.Collections.Generic;
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

namespace BNHealthMonitoring.UI.View
{
    /// <summary>
    /// Interaction logic for HelpView.xaml
    /// </summary>
    public partial class HelpView : UserControl
    {
        public HelpView()
        {
            InitializeComponent();
        }

        private void leftButtonClick(object p_sender, RoutedEventArgs p_e)
        {
            LeftMenu.BringIntoView();
        }

        private void homeButtonClick(object p_sender, RoutedEventArgs p_e)
        {
            Home.BringIntoView();
        }

        private void earthButtonClick(object p_sender, RoutedEventArgs p_e)
        {
            Earth.BringIntoView();
        }

        private void topButtonClick(object p_sender, RoutedEventArgs p_e)
        {
            Contents.BringIntoView();
        }
    }
}
