#include "Camera.hpp"
#include <cmath>

void Camera::update(float delta)
{
    float dx = x + (w / 2.0f) - focus->x;
    float dy = y + (h / 2.0f) - focus->y;
    xvel = -0.1f * floorf(engine::Util::getSign(dx) * sqrtf(abs(dx)));
    yvel = -0.1f * floorf(engine::Util::getSign(dy) * sqrtf(abs(dy)));
    engine::Camera::update(delta);
}
