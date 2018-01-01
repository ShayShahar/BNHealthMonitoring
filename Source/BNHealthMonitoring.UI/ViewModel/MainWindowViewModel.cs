using System.Collections.Generic;
using System.Reactive.Linq;
using System.Windows.Controls;
using System.Windows.Input;
using BNHealthMonitoring.UI.BL;
using BNHealthMonitoring.UI.View;
using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;
using System;

namespace BNHealthMonitoring.UI.ViewModel
{
    public class MainWindowViewModel : ViewModelBase
    {
        private readonly DataState m_dataState;
        private MessageDispatcher m_messageDispatcher;
        private bool m_isLogViewOpen;
        private bool m_isAboutViewOpen;
        private UserControl m_currentView;

        public MainWindowViewModel()
        {
            //  m_viewsContainer = new Dictionary<CurrentView, UserControl>();
            m_messageDispatcher = MessageDispatcher.GetInsatnce();
            m_dataState = DataState.GetInstance();
            m_dataState.ViewChanged.ObserveOnDispatcher().Subscribe(onSelectedViewChanged);
            m_currentView = new HomeView();
            //  m_viewsContainer.Add(CurrentView.HOME, new HomeView());
            //  m_viewsContainer.Add(CurrentView.EARTH, EarthView.GetInstance());

            //  View = m_viewsContainer[CurrentView.HOME];
        }

        public ICommand LogViewCommand
        {
            get
            {
                return new RelayCommand(onLogViewClick, () => true);
            }
        }

        //public UserControl View
        //{
        //    get { return m_currentView; }
        //    set
        //    {
        //        if (m_currentView == value)
        //            return;

        //        m_currentView = value;
        //        RaisePropertyChanged(() => View);
        //    }
        //}

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

        private void onSelectedViewChanged(DataState.RunningView p_view)
        {
            RaisePropertyChanged(() => CurrentView);
        }

        private void onHomeViewClick()
        {
            IsAboutViewOpen = false;
            IsLogViewOpen = false;

            if (m_currentView is HomeView)
                return;

            m_currentView = new HomeView();
        }

        private void onGlobeViewClick()
        {
            //if (m_current == CurrentView.EARTH)
            //    return;

            //m_current = CurrentView.EARTH;
       //     m_currentView = CurrentView.EARTH;

            IsAboutViewOpen = false;
            IsLogViewOpen = false;

            m_currentView = EarthView.GetInstance();
            RaisePropertyChanged(() => CurrentView);

            //m_currentView = EarthView.GetInstance();
            //RaisePropertyChanged(() => View);
        }

        public UserControl CurrentView
        {
            get { return m_currentView; }
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

    }
}