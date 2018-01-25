namespace Monitor.ViewApp
{
    using System;
    using System.Windows;

    using Monitor.ViewApp.BL;

    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private void App_OnExit(object p_sender, ExitEventArgs p_e)
        {
            try
            {
                MessageDispatcher.GetInsatnce().Dispose();
            }
            catch (Exception e)
            {
            }
        }
    }
}
