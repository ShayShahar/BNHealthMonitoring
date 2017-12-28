using System;
using BNHealthMonitoring.UI.BL;

namespace BNHealthMonitoring.UI.ViewModel
{
    public class PlotViewModel
    {
        private readonly MessageService m_messageService;
        private readonly DataState m_dataState;

        public PlotViewModel()
        {
            m_dataState = DataState.GetInstance();
            m_messageService = MessageService.GetInsatnce();
        }


    }
}
