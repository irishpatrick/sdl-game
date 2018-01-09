#ifndef ASSETS_H
#define ASSETS_H

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <future>
#include <iostream>
#include <thread>
#include <SDL.h>
#include <SDL_image.h>
#define BOOST_THREAD_VERSION 4
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>

#include "texture.h"

class Assets
{
public:
    Assets();
    ~Assets();

    void loadTexture(const std::string&, SDL_Renderer*);
    Texture* getTexture(const std::string&);
    void destroy();
    void getFutures();
    void useAll();

private:
    std::map<std::string, Texture*> texMap;
    std::vector<boost::future<void>> futures;
};

#endif /* ASSETS_H */