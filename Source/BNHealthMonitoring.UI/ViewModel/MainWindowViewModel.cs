using System.Collections.Generic;
using System.Reactive.Linq;
using System.Windows.Controls;
using System.Windows.Input;
using BNHealthMonitoring.UI.BL;
using BNHealthMonitoring.UI.View;
using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;
using System;
using System.Reactive;

namespace BNHealthMonitoring.UI.ViewModel
{
    public class MainWindowViewModel : ViewModelBase
    {
        private readonly DataState m_dataState;
        private bool m_isLogViewOpen;
        private bool m_isAboutViewOpen;

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
            get
            {
                return new RelayCommand(onLogViewClick, () => true);
            }
        }

        public ICommand AboutViewCommand
        {
            get
            {
                return new RelayCommand(onAboutViewClick, () => true);
            }
        }

        public ICommand HomeViewCommand
        {
            get
            {
                return new RelayCommand(onHomeViewClick, () => true);
            }
        }

        public ICommand GlobeViewCommand
        {
            get
            {
                return new RelayCommand(onGlobeViewClick, () => true);
            }
        }
        public ICommand AnalyzeViewCommand
        {
            get
            {
                return new RelayCommand(onAnalyzeViewClick, () => true);
            }
        }

        private void onSelectedViewChanged(Unit p_unit)
        {
            RaisePropertyChanged(() => CurrentView);
            RaisePropertyChanged(() => HomeViewImage);
            RaisePropertyChanged(() => EarthViewImage);
            RaisePropertyChanged(() => AnalyzeViewImage);
        }

        private void onHomeViewClick()
        {
            IsAboutViewOpen = false;
            IsLogViewOpen = false;

            if (m_dataState.CurrentView is HomeView)
                return;

            m_dataState.CurrentView = new HomeView();
        }

        private void onAnalyzeViewClick()
        {
            IsAboutViewOpen = false;
            IsLogViewOpen = false;

            if (m_dataState.CurrentView is AnalzyeView)
                return;

            m_dataState.CurrentView = new AnalzyeView();
        }

        private void onGlobeViewClick()
        {
            IsAboutViewOpen = false;
            IsLogViewOpen = false;

            m_dataState.CurrentView = EarthView.GetInstance();
        }

        public EarthView EarthView
        {
            get { return EarthView.GetInstance(); }
        }

        private void onAboutViewClick()
        {
            IsAboutViewOpen = !IsAboutViewOpen;
        }

        private void onLogViewClick()
        {
            IsLogViewOpen = !IsLogViewOpen;
        }

        public bool IsLogViewOpen
        {
            get { return m_isLogViewOpen; }
            set
            {
                m_isLogViewOpen = value;
                if (m_isLogViewOpen)
                    IsAboutViewOpen = false;
                RaisePropertyChanged(() => IsLogViewOpen);
            }
        }

        public bool IsAboutViewOpen
        {
            get { return m_isAboutViewOpen; }
            set
            {
                m_isAboutViewOpen = value;
                if (m_isAboutViewOpen)
                    IsLogViewOpen = false;
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

        public string AnalyzeViewImage
        {
            get
            {
                if (m_dataState.CurrentView is AnalzyeView)
                    return @"/Resources/analyze_selected.png";

                return @"/Resources/analyze.png";
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

    }
}