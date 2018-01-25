namespace Monitor.ViewApp.View
{
    using System.Windows;
    using System.Windows.Controls;

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
