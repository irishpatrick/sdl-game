#pragma once

#include <engine.hpp>

class Camera : public engine::Camera
{
public:
    Camera() {}
    ~Camera() {}

    void update(float) override;
};
