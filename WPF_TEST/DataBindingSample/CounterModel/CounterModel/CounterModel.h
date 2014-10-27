// CounterModel.h

#pragma once

#ifndef MAINWINDOWVIEWMODEL_H__
#define MAINWINDOWVIEWMODEL_H__

namespace DataBindingSample
{
	public ref class DelegateCommand : public System::Windows::Input::ICommand
	{
	public:
		DelegateCommand(System::Action<Object^>^ execute);
		DelegateCommand(System::Action<Object^>^ execute, System::Func<Object^, bool>^ canExecute);

		virtual void Execute(Object^ parameter);
		virtual bool CanExecute(Object^ parameter);
		virtual event System::EventHandler^ CanExecuteChanged;

	private:
		System::Action<Object^>^     execute_;
		System::Func<Object^, bool>^ canExecute_;
		static bool alwaysTrue(Object^ arg);
	};


	public ref class MainWindowViewModel : public System::ComponentModel::INotifyPropertyChanged
	{
	public:
		property int Count
		{
			int get();
			void set(int value);
		}

		virtual event System::ComponentModel::PropertyChangedEventHandler^ PropertyChanged;

		void attachCommand(System::Action<Object^>^ inc, System::Action<Object^>^ dec);
		void Update(int count);

		property System::Windows::Input::ICommand^ IncCommand
		{
			System::Windows::Input::ICommand^ get();
		}
		
		property System::Windows::Input::ICommand^ DecCommand
		{
			System::Windows::Input::ICommand^ get();
		}

	private:
		int _Count;
		System::Windows::Input::ICommand^ incCommand;
		System::Windows::Input::ICommand^ decCommand;
	};

	class Counter;

	public ref class CounterModel
	{
	public:
		CounterModel();
		!CounterModel();
		~CounterModel();

		// ModelÅ®ViewModel
		event System::Action<int>^ CountUpdated;

		// ViewModelÅ®Model 
		property System::Action<Object^>^ Increment
		{
			System::Action<Object^>^ get();
		}

		property System::Action<Object^>^ Decrement
		{
			System::Action<Object^>^ get();
		}

	private:
		Counter* counter_;
		void Notify();
		void inc(Object^ dummy);
		void dec(Object^ dummy);

	};

}

#endif

