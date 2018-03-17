#ifndef ASSETS_H
#define ASSETS_H

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <future>
#include <iostream>
#include <thread>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

namespace engine {

class Texture;

class Assets
{
public:

    static void loadTexture(const std::string&, SDL_Renderer*);
    static Texture* getTexture(const std::string&);
    static void destroy();
    static void getFutures();
    static void useAll();

private:
    static std::map<std::string, Texture*> texMap;
    static std::vector<std::future<void>> futures;
};

}

#endif /* ASSETS_H */
