#include "transition.hpp"

Transition::Transition() {
    attack = 0.0f;
    sustain = 0.0f;
    release = 0.0f;
    running = false;
    Type = NONE;
}

Transition::~Transition() {

}

// type of transition, attack, sustain, release
void Transition::start(Type t, float a, float s, float r) {
    type = t;
    attack = a;
    sustain = s;
    release = r;
    running = true;
}

void Transition::update(float delta) {

}
