using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using BNHealthMonitoring.UI.BL;
using BNHealthMonitoring.UI.View;
using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.CommandWpf;

namespace BNHealthMonitoring.UI.ViewModel
{
    public class HomeViewModel : ViewModelBase
    {
        public HomeViewModel()
        {
            
        }

        public EarthView EarthView
        {
            get { return EarthView.GetInstance(); }
        }
    }
}
