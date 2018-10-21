#include "Timer.hpp"

//auto then = std::chrono::high_resolution_clock::now();
//auto now = std::chrono::high_resolution_clock::now();

namespace engine
{

	long Timer::getNanoTime()
	{
		auto n = std::chrono::high_resolution_clock::now();
		auto duration = n.time_since_epoch();
		return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
	}

	float Timer::toSeconds(long t, Unit u)
	{
		if (u == NANO)
		{
			return t / 1.0e+9;
		}
		else if (u == MILLI)
		{
			return t / 1.0e+3;
		}
	}

	Timer::Timer()
	{
		duration = 0;
		//then = 0;
		//now = 0;
	}

	Timer::~Timer()
	{

	}

	void Timer::setInterval(long ms)
	{
		duration = ms * 1000 * 1000;
		reset();
	}

	void Timer::reset()
	{
		then = std::chrono::high_resolution_clock::now();
	}

	bool Timer::tick()
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

	void Timer::start()
	{
		reset();
		initial = getNanoTime();
	}

	long Timer::getElapsed()
	{
		return getNanoTime() - initial;
	}

	long Timer::getDelta()
	{
		now = std::chrono::high_resolution_clock::now();
		long delta = std::chrono::duration_cast<std::chrono::nanoseconds>(now - then).count();
		then = std::chrono::high_resolution_clock::now();
		return delta;
	}
}
