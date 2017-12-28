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
using BNHealthMonitoring.UI.BL;
using BNHealthMonitoring.UI.Model;
using MahApps.Metro.Controls;

namespace BNHealthMonitoring.UI.View
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : MetroWindow
    {
        private DataState m_dataState;

        public MainWindow()
        {
            InitializeComponent();
            m_dataState = DataState.GetInstance();
        }

        private void TreeView_SelectedItemChanged(object p_sender, RoutedPropertyChangedEventArgs<object> p_e)
        {
            m_dataState.SelectedComponent = (Component)p_e.NewValue;
        }
    }
}
