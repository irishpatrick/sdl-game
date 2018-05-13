#ifndef ASSETS_H
#define ASSETS_H

//#define BOOST_THREAD_PROVIDES_FUTURE
//#include <boost/thread.hpp>
//#include <boost/thread/future.hpp>
//#include <functional>
#include <map>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace engine {

class Texture;

class Assets {
public:

    static void loadTexture(const std::string&, SDL_Renderer*);
    static void loadTexturesFromVector(const std::string&, std::vector<std::string>, SDL_Renderer*);
    static void loadTexturesFromJson(const std::string&, const std::string&, SDL_Renderer*);
    static Texture* getTexture(const std::string&);
    static void destroy();
    //static void getFutures();
    static void useAll();

private:
    static std::map<std::string, Texture*> texMap;
    //static std::vector<boost::future<void>> futures;
};

}

#endif /* ASSETS_H */
