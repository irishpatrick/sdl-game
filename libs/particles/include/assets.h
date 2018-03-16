#ifndef PARTICLES_ASSETS_H
#define PARTICLES_ASSETS_H

#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "sol/sol.hpp"

using namespace std;

namespace particles {

class Assets {

public:
    static void registerAll(sol::state&);
    static string loadTexture(const string&);
    static void setRenderer(SDL_Renderer*);
    static SDL_Texture* getTexture(const string&);

private:
};

}

#endif /* PARTICLES_ASSETS_H */
