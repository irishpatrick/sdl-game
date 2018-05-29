#pragma once

#include "core_api.hpp"

#include <cstdint>
#include <SDL2/SDL.h>

namespace engine {

class Timer
{
public:
	CORE_API Timer();
	CORE_API ~Timer();

	CORE_API void SetInterval(double);
	CORE_API void Reset();
	CORE_API bool Tick();

private:
    double duration_;
    uint32_t then_;
    uint32_t now_;
};

}
