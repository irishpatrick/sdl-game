#ifndef ENGINE_CONTEXT_H
#define ENGINE_CONTEXT_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

using namespace std;

namespace engine {

class Context {

public:
    Context();
    ~Context();

    int init(int, int, const string&, bool);

    inline int getWidth() {
        return width;
    }

    inline int getHeight() {
        return height;
    }

    inline SDL_Window* getWindow() {
        return w;
    }

    inline SDL_Renderer* getRenderer() {
        return r;
    }

    inline void clear() {
        SDL_RenderClear(r);
    }

    inline void render() {
        SDL_RenderPresent(r);
    }

private:
    SDL_Window* w;
    SDL_Renderer* r;
    SDL_Event e;
    SDL_DisplayMode current;
    int width;
    int height;
};

}

#endif /* ENGINE_CONTEXT_H */
