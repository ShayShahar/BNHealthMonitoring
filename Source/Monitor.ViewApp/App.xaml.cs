using System;
using System.Diagnostics;
using System.Windows;
using Monitor.ViewApp.BL;

namespace Monitor.ViewApp
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        Process m_module = new Process();

        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            //m_module.StartInfo.WorkingDirectory = Directory.GetCurrentDirectory();
            //m_module.StartInfo.FileName = "BNHealthMonitoring.exe";
            //// p.StartInfo.CreateNoWindow = true;
            //m_module.Start();
        }

        private void App_OnExit(object p_sender, ExitEventArgs p_e)
        {
            try
            {
                MessageDispatcher.GetInsatnce().Dispose();
                //m_module.Kill();
            }
            catch (Exception e)
            {
                //do nothing
            }
        }
    }
}
