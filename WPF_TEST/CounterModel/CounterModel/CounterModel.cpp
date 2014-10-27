// これは メイン DLL ファイルです。

#include "stdafx.h"

#include "CounterModel.h"
#include "Counter.h"

#pragma comment(lib, "Counter.lib")

using namespace System;

namespace DataBindingSample
{
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

