namespace Monitor.ViewApp.ViewModel
{
    using System.Windows.Input;

    using BL;

    using GalaSoft.MvvmLight;
    using GalaSoft.MvvmLight.Command;

    using View;

    /// <summary>
    ///     HomeViewModel class stores the logic & data of the HomeView.
    ///     The main goal of the HomeViewModel is to handle user operations on the main program view.
    ///     This class inherits from Galasoft.MvvmLight.ViewModelBase which is the base class for any ViewModel in MVVM
    ///     pattern.
    /// </summary>
    public class HomeViewModel : ViewModelBase
    {
        #region Fields

        private readonly DataState m_dataState;

        #endregion

        #region Constructors and Destructors

        /// <summary>
        /// Initializes a new instance of the <see cref="HomeViewModel"/> class.
        /// </summary>
        public HomeViewModel()
        {
            m_dataState = DataState.GetInstance();
        }

        #endregion

        #region Public Properties

        /// <summary>
        /// Gets the earth view.
        /// </summary>
        public EarthView EarthView
        {
            get { return EarthView.GetInstance(); }
        }

        /// <summary>
        /// Gets the operation when user clicks on the expand button.
        /// </summary>
        public ICommand GlobeViewCommand
        {
            get { return new RelayCommand(onGlobeViewClick, () => true); }
        }

        #endregion

        #region Methods

        /// <summary>
        /// Expand the earth view button click logics.
        /// </summary>
        private void onGlobeViewClick()
        {
            m_dataState.CurrentView = EarthView.GetInstance();
        }

        #endregion
    }
}