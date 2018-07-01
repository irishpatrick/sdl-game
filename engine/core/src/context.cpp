#include "context.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

namespace engine {

	Context::Context() {

	}

	Context::~Context() {

	}

	int Context::init(int a, int b, const std::string& title, bool fullscreen) {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
			return -1;
		}

		if (!IMG_Init(IMG_INIT_PNG)) {
			std::cout << "IMG_Init error: " << IMG_GetError() << std::endl;
			return -1;
		}

		if (TTF_Init() < 0) {
			std::cout << "TTF_Init error: " << TTF_GetError() << std::endl;
		}

		if (SDL_GetDesktopDisplayMode(0, &current) < 0) {
			std::cout << "Display mode error " << SDL_GetTicks() << std::endl;
			return -1;
		}

		if (fullscreen) {
			width = current.w;
			height = current.h;
		} 
		else {
			width = a;
			height = b;
		}

		if (fullscreen) {
			w = SDL_CreateWindow(
				title.c_str(),
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				width,
				height,
				SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP
			);
		} 
		else {
			w = SDL_CreateWindow(
				title.c_str(),
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				width,
				height,
				SDL_WINDOW_OPENGL
			);
		}

		if (w == nullptr) {
			std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
			return -1;
		}

		r = SDL_CreateRenderer(
			w,
			-1,
			SDL_RENDERER_PRESENTVSYNC
		);

		if (r == nullptr) {
			std::cout << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
		}

		return 0;
	}

};
