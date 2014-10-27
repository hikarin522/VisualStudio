
#pragma once

#ifndef COUNTER_H_
#define COUNTER_H_

namespace DataBindingSample
{
	class Counter
	{
	public:
		void inc();
		void dec();
		int count();

	private:
		int count_;
	};
}

#endif /* COUNTER_H_ */
