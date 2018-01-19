using System.Windows.Input;
using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;
using Monitor.ViewApp.BL;
using Monitor.ViewApp.View;

namespace Monitor.ViewApp.ViewModel
{
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

        public HomeViewModel()
        {
            m_dataState = DataState.GetInstance();
        }

        #endregion

        #region Public Properties

        public EarthView EarthView
        {
            get { return EarthView.GetInstance(); }
        }

        public ICommand GlobeViewCommand
        {
            get { return new RelayCommand(onGlobeViewClick, () => true); }
        }

        #endregion

        #region Methods

        private void onGlobeViewClick()
        {
            m_dataState.CurrentView = EarthView.GetInstance();
        }

        #endregion
    }
}