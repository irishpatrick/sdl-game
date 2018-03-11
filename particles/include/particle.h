#ifndef PARTICLES_PARTICLE_H
#define PARTICLES_PARTICLE_H

#include <string>
#include <sstream>
#include "sol/sol.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

using namespace std;

namespace particles {

class Particle {

public:
    Particle();
    ~Particle();

    void draw(SDL_Renderer*);
    void script(const string&);
    void getFields();
    void update();
    string toString();

    int iterations;
    string texture;
    sol::state mylua;
    vector<sol::table> particles;
};

}

#endif /* PARTICLES_PARTICLE_H */
