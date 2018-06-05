#include "camera.hpp"
#include "sprite.hpp"

namespace engine {

	Camera::Camera() {
		x = 0;
		y = 0;
		fx = 0;
		fy = 0;
		w = 0;
		h = 0;
		focus = nullptr;
	}

	Camera::~Camera() {

	}

	void Camera::screen(int a, int b) {
		w = a;
		h = b;
	}

	void Camera::update(float delta ){
		if (focus != nullptr) {
			x = (w / 2.0f) - focus->x - (focus->w / 2.0f);
			y = (h / 2.0f) - focus->y - (focus->h / 2.0f);
		}
	}

	void Camera::setFocus(Sprite* s) {
		focus = s;
	}

}
