#pragma once

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

    inline float coordX(float x) {
        return (0.5f * x * width) + (width / 2.0f);
    }

    inline float coordY(float y) {
        return (0.5f * y * height) + (height / 2.0f);
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
