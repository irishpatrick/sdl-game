#pragma once

#include "core_api.hpp"

#include <cstdint>

namespace engine {

class Entity
{
public:
	CORE_API Entity();
	CORE_API virtual ~Entity();

	CORE_API virtual void pos(float, float);

    float x;
    float y;
    uint32_t w;
    uint32_t h;
};

}
