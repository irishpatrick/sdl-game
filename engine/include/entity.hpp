#pragma once

#include <cstdint>

namespace engine {

class Entity
{
public:
    Entity();
    virtual ~Entity();

    virtual void pos(float, float);

    float x;
    float y;
    uint32_t w;
    uint32_t h;
};

}
