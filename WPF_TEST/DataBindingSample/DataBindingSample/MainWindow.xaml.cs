using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using DataBindingSample;

namespace DataBindingSample
{
	/// <summary>
	/// MainWindow.xaml の相互作用ロジック
	/// </summary>

	public partial class App : Application
	{
		public static MainWindowViewModel ViewModel
		{
			get
			{
				if (viewmodel_ == null)
					viewmodel_ = new MainWindowViewModel();
				return viewmodel_;
			}
		}

		public static CounterModel Model
		{
			get
			{
				if (model_ == null)
					model_ = new CounterModel();
				return model_;
			}
		}

		public static MainWindowViewModel viewmodel_;
		public static CounterModel model_;
	}


	public partial class MainWindow : Window
	{
		public MainWindow()
		{
			InitializeComponent();
			this.DataContext = App.ViewModel;
			App.ViewModel.attachCommand(App.Model.Increment, App.Model.Decrement);
			App.Model.CountUpdated += App.ViewModel.Update;
		}
	}
}
