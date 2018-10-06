#pragma once

#include "core_api.hpp"
#include <cstdint>
#include <SDL2/SDL.h>
#include <chrono>

namespace engine {

enum Unit {NANO, MILLI};

class Timer
{
public:
	CORE_API Timer();
	CORE_API ~Timer();

	CORE_API void SetInterval(long);
	CORE_API void Reset();
	CORE_API bool Tick();

	CORE_API static long getNanoTime();
	CORE_API static float toSeconds(long, Unit);

private:
    //double duration;
    //uint32_t then;
    //uint32_t now;
	long duration;
	std::chrono::time_point<std::chrono::high_resolution_clock> now;
	std::chrono::time_point<std::chrono::high_resolution_clock> then;
	//std::chrono::time_point<std::chrono::steady_clock> now;
	//std::chrono::time_point<std::chrono::steady_clock> then;
};

}
