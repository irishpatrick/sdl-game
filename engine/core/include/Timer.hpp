#pragma once

#include "core_api.hpp"
#include <cstdint>
#include <SDL2/SDL.h>
#include <chrono>

namespace engine {

class Timer
{
public:
	CORE_API Timer();
	CORE_API ~Timer();

	CORE_API void SetInterval(long);
	CORE_API void Reset();
	CORE_API bool Tick();

private:
    //double duration;
    //uint32_t then;
    //uint32_t now;
	long duration;
	std::chrono::time_point<std::chrono::steady_clock> now;
	std::chrono::time_point<std::chrono::steady_clock> then;
};

}
