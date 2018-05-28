#pragma once

#include "dynamic.hpp"

#include <engine.hpp>

namespace ui {

class Decision {
public:
	Decision();
	~Decision();

	UI_API void update();
	UI_API void draw(engine::Context*);

	UI_API inline bool isVisible() { return visible; }

private:
	bool visible;

};

}
