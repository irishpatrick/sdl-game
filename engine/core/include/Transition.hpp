#pragma once

#include "core_api.hpp"
#include "Timer.hpp"
#include <cstdint>

namespace engine {

class Context;

enum Fade {FADE_IN, FADE_OUT};

class Transition {
public:
	CORE_API  Transition();
	CORE_API ~Transition();

	CORE_API inline void draw(Context* ctx) {
		fill(ctx, alpha);
	}

	CORE_API inline bool isRunning() {
        return running;
    }

	CORE_API void update();
	CORE_API void fadeOut(uint32_t);
	CORE_API void fadeIn(uint32_t);
	CORE_API void blockingFadeOut(Context*, uint32_t);
	CORE_API void blockingFadeIn(Context*, uint32_t);

private:
	CORE_API void fill(Context*, uint8_t);

	uint32_t start;
	uint32_t duration;
	uint8_t alpha;
	Fade fade;
	Timer timer;
    bool running;
};

}
