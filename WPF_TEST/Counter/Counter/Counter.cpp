
#include "Counter.h"

namespace DataBindingSample
{
	void Counter::inc()
	{
		++count_;
	}

	void Counter::dec()
	{
		--count_;
	}

	int Counter::count()
	{
		return count_;
	}
}
