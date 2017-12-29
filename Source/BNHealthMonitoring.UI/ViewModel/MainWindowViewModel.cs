using BNHealthMonitoring.UI.BL;
using GalaSoft.MvvmLight;

namespace BNHealthMonitoring.UI.ViewModel
{
    public class MainWindowViewModel : ViewModelBase
    {
        private MessageService m_messageService;
        private readonly DataState m_dataState;

        public MainWindowViewModel()
        {
            m_messageService = MessageService.GetInsatnce();
            m_dataState = DataState.GetInstance();
        }

    }
}
