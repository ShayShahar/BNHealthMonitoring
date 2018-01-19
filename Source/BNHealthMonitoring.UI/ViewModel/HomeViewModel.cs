using System.Windows.Input;
using GalaSoft.MvvmLight;
using Monitor.ViewApp.BL;
using Monitor.ViewApp.View;
using RelayCommand = GalaSoft.MvvmLight.Command.RelayCommand;

namespace Monitor.ViewApp.ViewModel
{
    public class HomeViewModel : ViewModelBase
    {
        private readonly DataState m_dataState;

        public HomeViewModel()
        {
            m_dataState = DataState.GetInstance();
        }

        public EarthView EarthView
        {
            get { return EarthView.GetInstance(); }
        }

        public ICommand GlobeViewCommand
        {
            get
            {
                return new RelayCommand(onGlobeViewClick, () => true);
            }
        }

        private void onGlobeViewClick()
        {
            m_dataState.CurrentView = EarthView.GetInstance();
        }
    }
}
