using GalaSoft.MvvmLight.Ioc;
using Microsoft.Practices.ServiceLocation;

namespace BNHealthMonitoring.UI.ViewModel
{
    /// <summary>
    /// This class contains static references to all the view models in the
    /// application and provides an entry point for the bindings.
    /// </summary>
    public class ViewModelLocator
    {
        /// <summary>
        /// Initializes a new instance of the ViewModelLocator class.
        /// </summary>
        public ViewModelLocator()
        {
            ServiceLocator.SetLocatorProvider(() => SimpleIoc.Default);
            SimpleIoc.Default.Register<MainWindowViewModel>();
            SimpleIoc.Default.Register<ProbabilityTableViewModel>();
            SimpleIoc.Default.Register<ComponentsTreeViewModel>();
            SimpleIoc.Default.Register<LocationChartViewModel>();
            SimpleIoc.Default.Register<AlgorithmOutputViewModel>();
            SimpleIoc.Default.Register<EarthViewModel>();
            SimpleIoc.Default.Register<LogViewModel>();
        }

        public MainWindowViewModel Main
        {
            get
            {
                return ServiceLocator.Current.GetInstance<MainWindowViewModel>();
            }
        }
        public ProbabilityTableViewModel Cpt
        {
            get
            {
                return ServiceLocator.Current.GetInstance<ProbabilityTableViewModel>();
            }
        }

        public LocationChartViewModel LocationChart
        {
            get
            {
                return ServiceLocator.Current.GetInstance<LocationChartViewModel>();
            }
        }

        public ComponentsTreeViewModel ComponentsTree
        {
            get
            {
                return ServiceLocator.Current.GetInstance<ComponentsTreeViewModel>();
            }
        }

        public AlgorithmOutputViewModel AlgorithmOutput
        {
            get
            {
                return ServiceLocator.Current.GetInstance<AlgorithmOutputViewModel>();
            }
        }

        public EarthViewModel Earth
        {
            get
            {
                return ServiceLocator.Current.GetInstance<EarthViewModel>();
            }
        }

        public LogViewModel Log
        {
            get
            {
                return ServiceLocator.Current.GetInstance<LogViewModel>();
            }
        }


        public static void Cleanup()
        {
            // TODO Clear the ViewModels
        }
    }
}