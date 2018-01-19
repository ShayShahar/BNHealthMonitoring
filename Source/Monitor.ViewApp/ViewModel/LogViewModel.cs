using System;
using System.Collections.ObjectModel;
using System.Reactive;
using System.Reactive.Linq;
using GalaSoft.MvvmLight;
using Monitor.ViewApp.BL;
using Monitor.ViewApp.Model;

namespace Monitor.ViewApp.ViewModel
{
    /// <summary>
    ///     LogViewModel class stores the logic & data of the LogView.
    ///     The main goal of the LogViewModel is to link between the messages list to the UI components.
    ///     This class inherits from Galasoft.MvvmLight.ViewModelBase which is the base class for any ViewModel in MVVM
    ///     pattern.
    /// </summary>
    public class LogViewModel : ViewModelBase
    {
        #region Fields

        private readonly DataState m_dataState;
        private readonly MessageDispatcher m_messageDispatcher;

        #endregion

        #region Constructors and Destructors

        public LogViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_messageDispatcher = MessageDispatcher.GetInsatnce();
            m_dataState.LogMessageUpdate.ObserveOnDispatcher().Subscribe(onLogMessageReceived);
        }

        #endregion

        #region Public Properties

        public ObservableCollection<LogItem> Messages
        {
            get { return m_dataState.IncomingMessagesLog; }
        }

        #endregion

        #region Methods

        private void onLogMessageReceived(Unit p_unit)
        {
            RaisePropertyChanged(() => Messages);
        }

        #endregion
    }
}