#include "particle.h"
#include "assets.h"

string rectToString(SDL_Rect* r) {
    ostringstream os;
    os << "x: " << r->x << " y: " << r->y << " w: " << r->w << " h: " << r->h;
    return os.str();
}

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

void Particle::update(float delta) {
    mylua["update"](delta);
}

void Particle::draw(SDL_Renderer* renderer) {
    for (int i=0; i<(int)mylua["num_particles"]; i++) {
        SDL_Rect rect;
        sol::table particle = mylua["particles"][i];
        mylua["set_start"](x,y);
        rect.x = (float)particle["x"];
        rect.y = (float)particle["y"];
        rect.w = (int)particle["w"];
        rect.h = (int)particle["h"];
        SDL_Texture* tex = Assets::getTexture(particle["texture"]);
        if (tex == nullptr) {
            cout << "tex not found!" << endl;
        }
        //cout << rectToString(&rect) << endl;
        SDL_RenderCopyEx(renderer, tex, nullptr, &rect, particle["angle"], nullptr, SDL_FLIP_NONE);
    }
}

}