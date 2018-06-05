#include "entity.hpp"

namespace engine {

	Entity::Entity() {
		x = 0;
		y = 0;
		w = 0;
		h = 0;
	}

	Entity::~Entity() {

	}

	void Entity::pos(float a, float b) {
		x = a;
		y = b;
	}

}
