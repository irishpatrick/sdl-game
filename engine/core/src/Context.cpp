#include "Context.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#ifdef _WIN32
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <ShellScalingApi.h>
#include <comdef.h>
#pragma comment(lib, "Shcore.lib")
#endif

namespace engine
{

	Context::Context()
	{

	}

	Context::~Context()
	{

	}

	int Context::init(int a, int b, const std::string& title, bool fullscreen)
	{
		#ifdef _WIN32
		HRESULT hr = SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
		if (FAILED(hr))
		{
			_com_error err(hr);
			std::cout << L"SetProcessDpiAwareness: " << err.ErrorMessage() << std::endl;
			//fwprintf(stderr, L"SetProcessDpiAwareness: %s\n", err.ErrorMessage());
		}
		#endif
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
			return -1;
		}

		if (!IMG_Init(IMG_INIT_PNG))
		{
			std::cout << "IMG_Init error: " << IMG_GetError() << std::endl;
			//return -1;
			std::cout << "We're not going to return, we'll just push on through" << std::endl;
		}

		if (TTF_Init() < 0)
		{
			std::cout << "TTF_Init error: " << TTF_GetError() << std::endl;
		}

		if (SDL_GetDesktopDisplayMode(0, &current) < 0)
		{
			std::cout << "Display mode error " << SDL_GetTicks() << std::endl;
			return -1;
		}

		if (fullscreen)
		{
			width = current.w;
			height = current.h;
		}
		else
		{
			width = a;
			height = b;
		}

		Uint32 flags;

		if (fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		else
		{
			flags = 0;
		}

		int scale = current.h / 1080;
		if (scale < 1) scale = 1;

		w = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width * scale,
			height * scale,
			flags
		);

		if (w == nullptr)
		{
			std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
			return -1;
		}

		r = SDL_CreateRenderer(
			w,
			-1,
			SDL_RENDERER_PRESENTVSYNC
		);

		SDL_RenderSetScale(r, (float)scale, (float)scale);

		if (r == nullptr)
		{
			std::cout << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
			return -1;
		}

		return 0;
	}
}
