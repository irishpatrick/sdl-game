#include "camera.hpp"
#include "sprite.hpp"
#include <iostream>

namespace engine {

	Camera::Camera() : Object() {
		fx = 0.0f;
		fy = 0.0f;
		w = -1;
		h = -1;
		focus = nullptr;
	}

	Camera::~Camera() {

	}

	void Camera::setScreen(int a, int b) {
		w = a;
		h = b;
	}

	void Camera::update(float delta) {
		if (w == -1 && h == -1) {
			std::cout << "need to set screen dimensions" << std::endl;
		}
		if (focus != nullptr) {
			x = (w / 2.0f) - focus->x - (focus->w / 2.0f);
			y = (h / 2.0f) - focus->y - (focus->h / 2.0f);
		}
	}

	void Camera::setFocus(Sprite* s) {
		focus = s;
	}

}
