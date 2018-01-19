using System;
using System.Reactive;
using System.Reactive.Linq;
using System.Windows.Controls;
using System.Windows.Input;
using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;
using Monitor.ViewApp.BL;
using Monitor.ViewApp.View;

namespace Monitor.ViewApp.ViewModel
{
    public class MainWindowViewModel : ViewModelBase
    {
        private readonly DataState m_dataState;
        private bool m_isAboutViewOpen;
        private bool m_isHelpViewOpen;
        private bool m_isLogViewOpen;

        public MainWindowViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_dataState.ViewChanged.ObserveOnDispatcher().Subscribe(onSelectedViewChanged);
            m_dataState.CurrentView = new HomeView();
        }

        public UserControl CurrentView
        {
            get { return m_dataState.CurrentView; }
        }

        public ICommand LogViewCommand
        {
            get { return new RelayCommand(onLogViewClick, () => true); }
        }

        public ICommand HelpViewCommand
        {
            get { return new RelayCommand(onHelpViewClick, () => true); }
        }

        public ICommand AboutViewCommand
        {
            get { return new RelayCommand(onAboutViewClick, () => true); }
        }

        public ICommand HomeViewCommand
        {
            get { return new RelayCommand(onHomeViewClick, () => true); }
        }

        public ICommand GlobeViewCommand
        {
            get { return new RelayCommand(onGlobeViewClick, () => true); }
        }

        public EarthView EarthView
        {
            get { return EarthView.GetInstance(); }
        }

        public bool IsLogViewOpen
        {
            get { return m_isLogViewOpen; }
            set
            {
                m_isLogViewOpen = value;

                if (m_isLogViewOpen)
                {
                    IsAboutViewOpen = false;
                    IsHelpViewOpen = false;
                }

                RaisePropertyChanged(() => IsLogViewOpen);
            }
        }

        public bool IsHelpViewOpen
        {
            get { return m_isHelpViewOpen; }
            set
            {
                m_isHelpViewOpen = value;

                if (m_isHelpViewOpen)
                {
                    IsAboutViewOpen = false;
                    IsLogViewOpen = false;
                }

                RaisePropertyChanged(() => IsHelpViewOpen);
            }
        }

        public bool IsAboutViewOpen
        {
            get { return m_isAboutViewOpen; }
            set
            {
                m_isAboutViewOpen = value;

                if (m_isAboutViewOpen)
                {
                    IsLogViewOpen = false;
                    IsHelpViewOpen = false;
                }

                RaisePropertyChanged(() => IsAboutViewOpen);
            }
        }

        public string HomeViewImage
        {
            get
            {
                if (m_dataState.CurrentView is HomeView)
                    return @"/Resources/home_selected.png";

                return @"/Resources/home.png";
            }
        }

        public string EarthViewImage
        {
            get
            {
                if (m_dataState.CurrentView is EarthView)
                    return @"/Resources/globe_selected.png";

                return @"/Resources/globe.png";
            }
        }

        private void onHelpViewClick()
        {
            IsHelpViewOpen = !IsHelpViewOpen;
        }

        private void onSelectedViewChanged(Unit p_unit)
        {
            RaisePropertyChanged(() => CurrentView);
            RaisePropertyChanged(() => HomeViewImage);
            RaisePropertyChanged(() => EarthViewImage);
        }

        private void onHomeViewClick()
        {
            IsAboutViewOpen = false;
            IsLogViewOpen = false;
            IsHelpViewOpen = false;

            if (m_dataState.CurrentView is HomeView)
                return;

            m_dataState.CurrentView = new HomeView();
        }

        private void onGlobeViewClick()
        {
            IsAboutViewOpen = false;
            IsLogViewOpen = false;
            IsHelpViewOpen = false;

            m_dataState.CurrentView = EarthView.GetInstance();
        }

        private void onAboutViewClick()
        {
            IsAboutViewOpen = !IsAboutViewOpen;
        }

        private void onLogViewClick()
        {
            IsLogViewOpen = !IsLogViewOpen;
        }
    }
}