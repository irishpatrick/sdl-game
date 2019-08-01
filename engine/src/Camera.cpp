#include "Camera.hpp"
#include "Sprite.hpp"
#include <iostream>

namespace engine
{

	Camera::Camera()
	{
		x = 0;
		y = 0;
		w = -1;
		h = -1;
		focus = nullptr;
	}

	Camera::~Camera()
	{

	}

    void Camera::init(Context& ctx)
    {
        setScreen(ctx.getWidth(), ctx.getHeight());
    }

	void Camera::setScreen(int a, int b)
	{
		w = a;
		h = b;
	}

	void Camera::update()
	{
		if (w == -1 && h == -1) {
			std::cout << "need to set screen dimensions" << std::endl;
		}
		if (focus != nullptr) {
			x = floorf(focus->x + (focus->w / 2.0f) - (getViewport().w / 2.0f));
    		y = floorf(focus->y + (focus->h / 2.0f) - (getViewport().h / 2.0f));
		}
	}

    void Camera::update(float delta)
    {
        x += xvel * delta;
        y += yvel * delta;
    }

	void Camera::setFocus(Sprite* s)
	{
		focus = s;
	}

    void Camera::setFocus(Sprite& s)
    {
        focus = &s;
    }

    BoundingBox Camera::getViewport()
    {
        return BoundingBox(x, y, w, h);
    }
}
