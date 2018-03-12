#include "particle.h"
#include "assets.h"

namespace particles {

Particle::Particle() {
    mylua.open_libraries(
        sol::lib::base,
        sol::lib::math,
        sol::lib::coroutine,
        sol::lib::string,
        sol::lib::io,
        sol::lib::os
    );

    x = 0;
    y = 0;

    Assets::registerAll(mylua);
}

Particle::~Particle() {

}

string Particle::toString() {
    ostringstream os;
    return os.str();
}

void Particle::getFields() {

}

void Particle::script(const string& fn) {
    mylua.script_file(fn);
    mylua["init"]();
}

void Particle::update() {
    mylua["update"]();
}

void Particle::draw(SDL_Renderer* renderer) {
    for (int i=0; i<(int)mylua["num_particles"]; i++) {
        SDL_Rect rect;
        sol::table particle = mylua["getparticle"](i);
        rect.x = x + particle["x"];
        rect.y = y + particle["y"];
        rect.w = particle["w"];
        rect.h = particle["h"];
        SDL_Texture* tex = Assets::getTexture(particle["texture"]);

        SDL_RenderCopyEx(renderer, tex, nullptr, &rect, particle["angle"], nullptr, SDL_FLIP_NONE);
    }
}

}
