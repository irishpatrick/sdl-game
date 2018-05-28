#pragma once

#include <cstdint>

namespace engine {

class Context;

enum Fade {IN, OUT};

class Transition {
public:
    Transition();
    ~Transition();

	inline void draw(Context* ctx) {
		fill(ctx, alpha);
	}

    inline bool isRunning() {
        return running;
    }

    void update();
	void fadeOut(uint32_t);
	void fadeIn(uint32_t);
	void blockingFadeOut(Context*, uint32_t);
	void blockingFadeIn(Context*, uint32_t);

private:
    void fill(Context*, uint8_t);

	uint32_t start;
	uint32_t duration;
	uint8_t alpha;
	Fade fade;
    bool running;
};

}
