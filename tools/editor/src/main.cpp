#include <iostream>
#include <cstdint>
#include <engine.hpp>
#include "editor.hpp"

bool quit;
SDL_Event e;
engine::Context ctx;
engine::State* current;

Editor editor;

void init() {
	ctx.init(1024, 768, "Editor", false);
	quit = false;
}

void render() {
	float delta;
	uint32_t now;
	uint32_t then = SDL_GetTicks();

	while (!quit) {
		now = SDL_GetTicks();
		delta = now - then;

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		int x;
		int y;
		SDL_GetMouseState(&x, &y);

		const uint8_t* state = SDL_GetKeyboardState(nullptr);
		if (state[SDL_SCANCODE_ESCAPE])
		{
			quit = true;
		}

		current->update(delta / 1000.0f, state);

		ctx.clear();
		current->render(ctx);
		ctx.render();

		then = now;
	}
}

void cleanup() {
	current = nullptr;
	editor.destroy();
	ctx.destroy();
}

int main(int argc, char** argv) {
    std::cout << "hello world" << std::endl;
	
	init();

	editor.init(ctx);

	current = &editor;

    return 0;
}
