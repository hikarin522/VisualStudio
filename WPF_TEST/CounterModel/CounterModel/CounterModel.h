// CounterModel.h

#pragma once

using namespace System;

namespace DataBindingSample
{
	class Counter;

	public ref class CounterModel
	{
	public:
		CounterModel();
		!CounterModel();
		~CounterModel();

		// Model -> ViewModel
		event System::Action<int>^ CountUpdated;

		// ViewModel -> Model
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
