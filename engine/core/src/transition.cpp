#include "transition.hpp"
#include "util.hpp"
#include "context.hpp"
#include <SDL2/SDL.h>
#include <cmath>

namespace engine {

Transition::Transition() {
	alpha = 0;
	duration = 0;
	running = false;
}

Transition::~Transition() {

}

void Transition::blockingFadeOut(Context* ctx, uint32_t d) {
	if (!running) {
		fadeOut(d);
	}
	while (running) {
		update();
		draw(ctx);
	}
}

void Transition::blockingFadeIn(Context* ctx, uint32_t d) {
	if (!running) {
		fadeIn(d);
	}
	while (running) {
		update();
		draw(ctx);
	}
}

void Transition::fadeOut(uint32_t d) {
	if (!running) {
		running = true;
		duration = d;
		start = SDL_GetTicks();
		fade = OUT;
	}
}

void Transition::fadeIn(uint32_t d) {
	if (!running) {
		running = true;
		duration = d;
		start = SDL_GetTicks();
		fade = IN;
	}
}

void Transition::fill(Context* ctx, uint8_t alpha) {
    SDL_SetRenderDrawBlendMode(ctx->getRenderer(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(ctx->getRenderer(), 0, 0, 0, alpha);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 512;
    rect.h = 480;
    SDL_RenderFillRect(ctx->getRenderer(), &rect);
	SDL_SetRenderDrawColor(ctx->getRenderer(), 0, 0, 0, 255);
}

void Transition::update() {
    if (running) {
		uint32_t now = SDL_GetTicks();
        uint32_t delta = now - start;
		float t = (float)delta / (float)(duration);
		if (t >= 1.0f) {
			running = false;
			t = 1.0f;
		}
        float lerp;
		if (fade == OUT) {
			lerp = Util::lerp(t, 0.0f, 255.0f);
		}
		else if (fade == IN) {
			lerp = Util::lerp(t, 255.0f, 0.0f);
		}
        alpha = (uint8_t)lerp;
    }
}

}
