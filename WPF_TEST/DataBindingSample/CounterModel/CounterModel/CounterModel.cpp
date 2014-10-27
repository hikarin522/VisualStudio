// これは メイン DLL ファイルです。

#include "stdafx.h"

#include "CounterModel.h"
#include "Counter.h"

#pragma comment(lib, "Counter.lib")

using namespace System;
using namespace System::Windows::Input;


namespace DataBindingSample
{
	// DelegateCommand
	DelegateCommand::DelegateCommand(Action<Object^>^ execute)
	{
		execute_ = execute;
		canExecute_ = gcnew Func<Object^, bool>(DelegateCommand::alwaysTrue);
	}

	DelegateCommand::DelegateCommand(Action<Object^>^ execute, Func<Object^, bool>^ canExecute)
	{
		execute_ = execute;
		canExecute_ = canExecute;
	}

	bool DelegateCommand::CanExecute(Object^ parameter)
	{
		return canExecute_(parameter);
	}
	void DelegateCommand::Execute(Object^ parameter)
	{
		execute_(parameter);
	}
	bool DelegateCommand::alwaysTrue(Object^ arg)
	{
		return true;
	}


	// MainWindowViewModel
	int MainWindowViewModel::Count::get()
	{
		return _Count;
	}

	void MainWindowViewModel::Count::set(int count)
	{
		_Count = count;
		PropertyChanged(this, gcnew System::ComponentModel::PropertyChangedEventArgs("Count"));
	}

	void MainWindowViewModel::Update(int count)
	{
		Count = count;
	}

	Windows::Input::ICommand^ MainWindowViewModel::IncCommand::get()
	{
		return incCommand;
	}

	Windows::Input::ICommand^ MainWindowViewModel::DecCommand::get()
	{
		return decCommand;
	}

	void MainWindowViewModel::attachCommand(Action<Object^>^ inc, Action<Object^>^ dec)
	{
		incCommand = gcnew DelegateCommand(inc);
		decCommand = gcnew DelegateCommand(dec);
	}


	// CounterModel
	CounterModel::CounterModel()
	{
		counter_ = new Counter();
	}

	CounterModel::!CounterModel()
	{
		this->~CounterModel();
	}

	CounterModel::~CounterModel()
	{
		delete counter_;
	}

	Action<Object^>^ CounterModel::Increment::get()
	{
		return gcnew Action<Object^>(this, &CounterModel::inc);
	}

	Action<Object^>^ CounterModel::Decrement::get()
	{
		return gcnew Action<Object^>(this, &CounterModel::dec);
	}

	void CounterModel::Notify()
	{
		CountUpdated(counter_->count());
	}

	void CounterModel::inc(Object^ dummy)
	{
		counter_->inc();
		Notify();
	}

	void CounterModel::dec(Object^ dummy)
	{
		counter_->dec();
		Notify();
	}
}

