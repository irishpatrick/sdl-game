#include "context.h"

namespace engine {

Context::Context() {

}

Context::~Context() {

}

int Context::init(int a, int b, const string& title, bool fullscreen) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) {
        cout << "SDL_Init error: " << SDL_GetError() << endl;
        return -1;
    }

    if (SDL_GetDesktopDisplayMode(0, &current) < 0) {
        cout << "Display mode error " << SDL_GetTicks() << endl;
        return -1;
    }

    if (fullscreen) {
        width = current.w;
        height = current.h;
    } else {
        width = a;
        height = b;
    }

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        cout << "SDL_CreateWindow error: " << SDL_GetError(); << endl;
        return -1;
    }

    
}

};
