namespace Monitor.ViewApp.ViewModel
{
    using System;
    using System.Collections.ObjectModel;
    using System.Reactive;
    using System.Reactive.Linq;

    using BL;

    using GalaSoft.MvvmLight;

    using Model;

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

        /// <summary>
        /// Initializes a new instance of the <see cref="LogViewModel"/> class.
        /// </summary>
        public LogViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_messageDispatcher = MessageDispatcher.GetInsatnce();
            m_dataState.LogMessageUpdate.ObserveOnDispatcher().Subscribe(onLogMessageReceived);
        }

        #endregion

        #region Public Properties

        /// <summary>
        /// Gets the messages which stored at the DataState.
        /// </summary>
        public ObservableCollection<LogItem> Messages
        {
            get { return m_dataState.IncomingMessagesLog; }
        }

        #endregion

        #region Methods

        /// <summary>
        /// This function invokes where a new message received.
        /// </summary>
        private void onLogMessageReceived(Unit p_unit)
        {
            RaisePropertyChanged(() => Messages);
        }

        #endregion
    }
}