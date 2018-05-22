#include "transition.hpp"
#include "util.hpp"
#include "context.hpp"
#include <SDL2/SDL.h>

namespace engine {

Transition::Transition(Context* c) {
    ctx = c;
    initial = 0;
    attack = 0;
    sustain = 0;
    release = 0;
}

Transition::~Transition() {

}

void Transition::fill(uint8_t alpha) {
    SDL_SetRenderDrawColor(ctx->getRenderer(), 0, 0, 0, alpha);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 512;
    rect.h = 480;
    SDL_RenderFillRect(ctx->getRenderer(), &rect);
}

// type of transition, attack, sustain, release
void Transition::start(Type t, uint32_t a, uint32_t s, uint32_t r) {
    type = t;
    attack = a;
    sustain = s;
    release = r;
    running = true;
    initial = SDL_GetTicks();
}

void Transition::update() {
    if (running) {
        uint32_t current = SDL_GetTicks();
        if (current < initial + attack) {
            float t = (float)current / (float)(initial + attack);
            fill((uint8_t)Util::lerp(0, 255, t));
        }
        else if (current < initial + attack + sustain) {
            //float t = (float)current / (float)(initial + attack + sustain);
            fill(255);
        }
        else if (current < initial + attack + sustain + release) {
            float t = (float)current / (float)(initial + attack + sustain + release);
            fill((uint8_t)Util::lerp(255, 0, t));
        }
    }
}

}
