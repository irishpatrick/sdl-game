#pragma once

#include <cstdint>

namespace engine {

class Context;

enum Fade {IN, OUT};

class Transition {
public:
    Transition(Context*);
    ~Transition();

    void update();
	void draw(Context*);
	void fadeOut(uint32_t);
	void fadeIn(uint32_t);

private:
    void fill(Context*, uint8_t);

	uint32_t start;
	uint32_t duration;
	uint8_t alpha;
	Fade fade;
    bool running;
};

}
