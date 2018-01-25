namespace Monitor.ViewApp.ViewModel
{
    using System;
    using System.Reactive;
    using System.Reactive.Linq;
    using System.Windows.Controls;
    using System.Windows.Input;

    using BL;

    using GalaSoft.MvvmLight;
    using GalaSoft.MvvmLight.Command;

    using View;

    /// <summary>
    ///     MainWindowViewModel class stores the logic & data of the MainWindowView.
    ///     The main goal of the MainWindowViewModel is to link between the user's selected view to the UI components.
    ///     The class handles the main framework of the application.
    ///     This class inherits from Galasoft.MvvmLight.ViewModelBase which is the base class for any ViewModel in MVVM
    ///     pattern.
    /// </summary>
    public class MainWindowViewModel : ViewModelBase
    {
        #region Fields

        private readonly DataState m_dataState;

        private bool m_isAboutViewOpen;

        private bool m_isHelpViewOpen;

        private bool m_isLogViewOpen;

        #endregion

        #region Constructors and Destructors

        /// <summary>
        /// Initializes a new instance of the <see cref="MainWindowViewModel"/> class.
        /// </summary>
        public MainWindowViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_dataState.ViewChanged.ObserveOnDispatcher().Subscribe(onSelectedViewChanged);
            m_dataState.CurrentView = new HomeView();
        }

        #endregion

        #region Public Properties

        /// <summary>
        /// Gets the log button click command.
        /// </summary>
        public ICommand LogViewCommand
        {
            get
            {
                return new RelayCommand(onLogViewClick, () => true);
            }
        }

        /// <summary>
        /// Gets the earth button click command.
        /// </summary>
        public ICommand GlobeViewCommand
        {
            get
            {
                return new RelayCommand(onGlobeViewClick, () => true);
            }
        }

        /// <summary>
        /// Gets the help button click command.
        /// </summary>
        public ICommand HelpViewCommand
        {
            get
            {
                return new RelayCommand(onHelpViewClick, () => true);
            }
        }

        /// <summary>
        /// Gets the home button click command.
        /// </summary>
        public ICommand HomeViewCommand
        {
            get
            {
                return new RelayCommand(onHomeViewClick, () => true);
            }
        }

        /// <summary>
        /// Gets the about button click command.
        /// </summary>
        public ICommand AboutViewCommand
        {
            get
            {
                return new RelayCommand(onAboutViewClick, () => true);
            }
        }

        /// <summary>
        /// Gets the current view from DataState.
        /// </summary>
        public UserControl CurrentView
        {
            get
            {
                return m_dataState.CurrentView;
            }
        }

        /// <summary>
        /// Gets the earth view instance.
        /// </summary>
        public EarthView EarthView
        {
            get
            {
                return EarthView.GetInstance();
            }
        }

        /// <summary>
        /// Gets the earth view button image.
        /// </summary>
        public string EarthViewImage
        {
            get
            {
                if (m_dataState.CurrentView is EarthView)
                {
                    return @"/Resources/globe_selected.png";
                }

                return @"/Resources/globe.png";
            }
        }

        /// <summary>
        /// Gets the home view button image.
        /// </summary>
        public string HomeViewImage
        {
            get
            {
                if (m_dataState.CurrentView is HomeView)
                {
                    return @"/Resources/home_selected.png";
                }

                return @"/Resources/home.png";
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether the about view open.
        /// </summary>
        /// <value><c>true</c> if the about view open; otherwise, <c>false</c>.</value>
        public bool IsAboutViewOpen
        {
            get
            {
                return m_isAboutViewOpen;
            }

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

        /// <summary>
        /// Gets or sets a value indicating whether the help view open.
        /// </summary>
        /// <value><c>true</c> if the help view open; otherwise, <c>false</c>.</value>
        public bool IsHelpViewOpen
        {
            get
            {
                return m_isHelpViewOpen;
            }

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

        /// <summary>
        /// Gets or sets a value indicating whether the log view open.
        /// </summary>
        /// <value><c>true</c> if the log view open; otherwise, <c>false</c>.</value>
        public bool IsLogViewOpen
        {
            get
            {
                return m_isLogViewOpen;
            }

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

        #endregion

        #region Methods

        /// <summary>
        /// About button click logics.
        /// </summary>
        private void onAboutViewClick()
        {
            IsAboutViewOpen = !IsAboutViewOpen;
        }

        /// <summary>
        /// Earth button click logics.
        /// </summary>
        private void onGlobeViewClick()
        {
            IsAboutViewOpen = false;
            IsLogViewOpen = false;
            IsHelpViewOpen = false;

            m_dataState.CurrentView = EarthView.GetInstance();
        }

        /// <summary>
        /// Help button click logics.
        /// </summary>
        private void onHelpViewClick()
        {
            IsHelpViewOpen = !IsHelpViewOpen;
        }

        /// <summary>
        /// Home button click logics.
        /// </summary>
        private void onHomeViewClick()
        {
            IsAboutViewOpen = false;
            IsLogViewOpen = false;
            IsHelpViewOpen = false;

            if (m_dataState.CurrentView is HomeView)
            {
                return;
            }

            m_dataState.CurrentView = new HomeView();
        }

        /// <summary>
        /// Log button click logics.
        /// </summary>
        private void onLogViewClick()
        {
            IsLogViewOpen = !IsLogViewOpen;
        }


        /// <summary>
        /// This function invokes where the user switches between the application's screens.
        /// </summary>
        private void onSelectedViewChanged(Unit p_unit)
        {
            RaisePropertyChanged(() => CurrentView);
            RaisePropertyChanged(() => HomeViewImage);
            RaisePropertyChanged(() => EarthViewImage);
        }

        #endregion
    }
}