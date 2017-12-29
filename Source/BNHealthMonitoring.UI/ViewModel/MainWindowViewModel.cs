using BNHealthMonitoring.UI.BL;
using GalaSoft.MvvmLight;

namespace BNHealthMonitoring.UI.ViewModel
{
    public class MainWindowViewModel : ViewModelBase
    {
        private readonly DataState m_dataState;
        private MessageService m_messageService;

        public MainWindowViewModel()
        {
            m_messageService = MessageService.GetInsatnce();
            m_dataState = DataState.GetInstance();
        }
    }
}