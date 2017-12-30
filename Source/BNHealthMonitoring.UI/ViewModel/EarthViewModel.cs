using System.Reactive;
using System.Reactive.Linq;
using System.Windows.Input;
using BNHealthMonitoring.UI.BL;
using BNHealthMonitoring.UI.View;
using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;
using HelixToolkit.Wpf;
using System;

namespace BNHealthMonitoring.UI.ViewModel
{
    public class EarthViewModel : ViewModelBase
    {
        private readonly DataState m_dataState;
        private HelixViewport3D m_earthViewPort;
        private SphereVisual3D m_earthSphere;

        public EarthViewModel()
        {
            m_dataState = DataState.GetInstance();
            Earth = new HelixViewport3D();
        }

        public SphereVisual3D EarthSphere
        {
            get { return m_earthSphere; }
            set
            {
                m_earthSphere = value;
                RaisePropertyChanged(() => EarthSphere);
            }
        }


        private void onWindowLoadedCommand(Unit p_unit)
        {
            Earth.ZoomExtents();
        }

        public HelixViewport3D Earth
        {
            get { return m_earthViewPort; }
            set
            {
                m_earthViewPort = value;
                RaisePropertyChanged(() => Earth);

            }
        }
    }
}
