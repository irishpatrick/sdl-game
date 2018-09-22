#include "Timer.hpp"

namespace engine
{

	Timer::Timer()
	{
		duration = 0;
		//then = 0;
		//now = 0;
	}

	Timer::~Timer()
	{

	}

	void Timer::SetInterval(long ms)
	{
		duration = ms * 1000 * 1000;
		Reset();
	}

	void Timer::Reset()
	{
		then = std::chrono::high_resolution_clock::now();
	}

	bool Timer::Tick()
	{
		now = std::chrono::high_resolution_clock::now();
		long delta = std::chrono::duration_cast<std::chrono::nanoseconds>(now - then).count();
		if (delta >= duration)
		{
			then = std::chrono::high_resolution_clock::now();
			return true;
		}
		return false;
	}
}
