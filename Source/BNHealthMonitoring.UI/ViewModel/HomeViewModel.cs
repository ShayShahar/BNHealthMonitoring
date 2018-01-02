using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using BNHealthMonitoring.UI.BL;
using BNHealthMonitoring.UI.View;
using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.CommandWpf;
using RelayCommand = GalaSoft.MvvmLight.Command.RelayCommand;

namespace BNHealthMonitoring.UI.ViewModel
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
