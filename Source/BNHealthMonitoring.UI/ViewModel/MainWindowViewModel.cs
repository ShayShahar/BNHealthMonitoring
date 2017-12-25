using System;
using System.Collections.Generic;
using System.Linq;
using System.Reactive;
using System.Reactive.Linq;
using System.Text;
using System.Threading.Tasks;
using BNHealthMonitoring.UI.BL;
using BNHealthMonitoring.UI.Model;
using GalaSoft.MvvmLight;

namespace BNHealthMonitoring.UI.ViewModel
{
    public class MainWindowViewModel : ViewModelBase
    {
        private IList<Component> m_components;
        private readonly MessageService m_messageService;

        public MainWindowViewModel()
        {
            m_components = new List<Component>();
            Component c = new Component
            {
                Name = "Sattelite Alpha",
                Children = new List<Component>
                {
                    new Component
                    {
                        Name = "GPS"
                    },
                    new Component
                    {
                        Name = "Magnometer"
                    }
                }
            };
            m_components.Add(c);
            m_messageService = MessageService.GetInsatnce();
            m_messageService.ComponentsUpdate.ObserveOnDispatcher().Subscribe(onComponentsUpdateEvent);
            LabelText = "Hello";
        }

        public string LabelText { get; set; }

        public IList<Component> Components
        {
            get { return m_components; }
            set
            {
                m_components = value;
                RaisePropertyChanged();
            }
        }

        private void onComponentsUpdateEvent(Unit p_unit)
        {
            RaisePropertyChanged(() => Components);
        }
    }
}
