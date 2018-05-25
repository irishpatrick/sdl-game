#include "transition.hpp"
#include "util.hpp"
#include "context.hpp"
#include <SDL2/SDL.h>

namespace engine {

Transition::Transition() {
	alpha = 0;
	duration = 0;
	running = false;
}

Transition::~Transition() {

}

void Transition::fadeOut(uint32_t d) {
	if (!running) {
		running = true;
		duration = d * 1000;
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
		float t = (float)now / (float)(start + duration);
		if (now > start + duration) {
			running = false;
			t = 1.0f;
		}
		if (fade == OUT) {
			alpha = Util::lerp(0.0f, 255.0f, t);
		}
		else if (fade == IN) {
			alpha = Util::lerp(255.0f, 0.0f, t);
		}
    }
}

}
