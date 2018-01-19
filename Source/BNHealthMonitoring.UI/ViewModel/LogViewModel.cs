using System;
using System.Collections.ObjectModel;
using System.Reactive;
using System.Reactive.Linq;
using GalaSoft.MvvmLight;
using Monitor.ViewApp.BL;
using Monitor.ViewApp.Model;

namespace Monitor.ViewApp.ViewModel
{
    public class LogViewModel : ViewModelBase
    {
        private readonly DataState m_dataState;
        private readonly MessageDispatcher m_messageDispatcher;

        public LogViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_messageDispatcher = MessageDispatcher.GetInsatnce();
            m_dataState.LogMessageUpdate.ObserveOnDispatcher().Subscribe(onLogMessageReceived);
        }

        public ObservableCollection<LogItem> Messages
        {
            get { return m_dataState.IncomingMessagesLog; }
        } 

        private void onLogMessageReceived(Unit p_unit)
        {
            RaisePropertyChanged(()=> Messages);
        }
    }
}
