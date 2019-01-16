#pragma once

#include "core_api.hpp"
#include <cstdint>
#include <SDL.h>
#include <chrono>

namespace engine {

enum Unit {NANO, MILLI};

class Timer
{
public:
	CORE_API Timer();
	CORE_API ~Timer();

	CORE_API void setInterval(long);
	CORE_API void reset();
	CORE_API bool tick();
	CORE_API void start();
	CORE_API long getElapsed();
	CORE_API long getDelta();

	CORE_API static long getNanoTime();
	CORE_API static float toSeconds(long, Unit);

private:
	long duration;
	long initial;

	std::chrono::time_point<std::chrono::high_resolution_clock> now;
	std::chrono::time_point<std::chrono::high_resolution_clock> then;
};

}
