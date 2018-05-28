#pragma once

#include <engine.hpp>

namespace ui {

class Decision {
public:
	Decision();
	~Decision();

	void update();
	void draw(engine::Context*);

	inline bool isVisible() { return visible; }

private:
	bool visible;

};

}
