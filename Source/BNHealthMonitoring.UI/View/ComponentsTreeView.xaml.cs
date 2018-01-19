using System.Windows;
using System.Windows.Controls;
using Monitor.ViewApp.BL;
using Monitor.ViewApp.Model;

namespace Monitor.ViewApp.View
{
    /// <summary>
    /// Interaction logic for ComponentsTreeView.xaml
    /// </summary>
    public partial class ComponentsTreeView : UserControl
    {
        private DataState m_dataState;

        public ComponentsTreeView()
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
