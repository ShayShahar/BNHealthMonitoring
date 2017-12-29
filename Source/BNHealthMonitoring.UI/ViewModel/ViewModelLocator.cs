/*
  In App.xaml:
  <Application.Resources>
      <vm:ViewModelLocator xmlns:vm="clr-namespace:BNHealthMonitoring.UI"
                           x:Key="Locator" />
  </Application.Resources>
  
  In the View:
  DataContext="{Binding Source={StaticResource Locator}, Path=ViewModelName}"

  You can also use Blend to do all this with the tool's support.
  See http://www.galasoft.ch/mvvm
*/

using GalaSoft.MvvmLight;
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

        public static void Cleanup()
        {
            // TODO Clear the ViewModels
        }
    }
}