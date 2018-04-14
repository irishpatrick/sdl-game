#include <iostream>
#include <SDL2/SDL.h>
#include <engine.h>

using namespace std;

SDL_Window* w;
SDL_Renderer* r;
SDL_Event e;
bool running;

void init() {
    
}

int main(int argc, char** argv) {
    cout << "hello, world!" << endl;
    init();
    return 0;
}
