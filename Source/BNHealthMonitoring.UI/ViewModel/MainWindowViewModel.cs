using System.Windows.Input;
using BNHealthMonitoring.UI.BL;
using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;

namespace BNHealthMonitoring.UI.ViewModel
{
    public class MainWindowViewModel : ViewModelBase
    {
        private readonly DataState m_dataState;
        private MessageDispatcher m_messageDispatcher;
        private bool m_isLogViewOpen;
        private bool m_isAboutViewOpen;

        public MainWindowViewModel()
        {
            m_messageDispatcher = MessageDispatcher.GetInsatnce();
            m_dataState = DataState.GetInstance();
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