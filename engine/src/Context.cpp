#include "Context.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdint>
#include "Game.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

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

    Context::Context() :
		camera(nullptr),
        width(-1),
        height(-1),
        quitCallback(nullptr),
        w(nullptr),
        r(nullptr),
        scale(0.0f)
	{
		Settings def;
		def.useCamera = true;
		def.mode = SDL_BLENDMODE_BLEND;
		cfg.push(def);
	}

	Context::~Context()
	{
        destroy();
	}

	void Context::pushCfg()
	{
		Settings mod = cfg.top();
		cfg.push(mod);
	}

	Settings* Context::getCfg()
	{
		return &cfg.top();
	}

	void Context::popCfg()
	{
		if (cfg.size() < 2)
		{
			return;
		}

		cfg.pop();
	}

	void Context::applyCfg()
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

        std::cout << "init video\n";
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		{
			std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
			return -1;
		}

        std::cout << "init img\n";
		if (!IMG_Init(IMG_INIT_PNG))
		{
			std::cout << "IMG_Init error: " << IMG_GetError() << std::endl;
			//return -1;
			std::cout << "We're not going to return, we'll just push on through" << std::endl;
		}

        std::cout << "init ttf\n";
		if (TTF_Init() < 0)
		{
			std::cout << "TTF_Init error: " << TTF_GetError() << std::endl;
		}

        std::cout << "get display\n";
        SDL_DisplayMode current;
		if (SDL_GetDesktopDisplayMode(0, &current) < 0)
		{
			std::cout << "Display mode error " << SDL_GetError() << std::endl;
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

		std::cout << "monitor height: " << current.h << std::endl;
		scale = (double)current.h / 1080;
		if (scale < 1) scale = 1;

        std::cout << "create window\n";

		w = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width * (uint32_t)scale,
			height * (uint32_t)scale,
			flags
		);

		if (w == nullptr)
		{
			std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
			return -1;
		}

        std::cout << "create renderer\n";

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

	void Context::setQuitCallback(void(*callback)(void))
	{
		quitCallback = callback;
	}

	void Context::pollEvents()
	{
        SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				if (quitCallback != nullptr)
				{
					quitCallback();
				}

				Game::quit();
			}
		}
	}

	void Context::draw(Texture* t, SDL_Rect* dst)
	{
		Settings* cur = &cfg.top();
		SDL_SetTextureBlendMode(t->use(), cur->mode);
		draw(t, nullptr, dst);
	}

	void Context::draw(Texture* t, SDL_Rect* src, SDL_Rect* dst)
	{
		Settings* cur = &cfg.top();

		if (cur->useCamera)
		{
			applyCamera(dst);
		}
		SDL_SetTextureBlendMode(t->use(), cur->mode);
		SDL_RenderCopy(r, t->use(), src, dst);
	}

	void Context::draw(Texture* t, SDL_Rect* src, SDL_Rect* dst, double theta, SDL_Point* center, SDL_RendererFlip flip)
	{
		Settings* cur = &cfg.top();

		if (cur->useCamera)
		{
			applyCamera(dst);
		}
		SDL_SetTextureBlendMode(t->use(), cur->mode);
		SDL_RenderCopyEx(r, t->use(), src, dst, theta, center, flip);
	}

    BoundingBox Context::getBoundingBox()
    {
        return BoundingBox(0, 0, width, height);
    }

	void Context::applyCamera(SDL_Rect* r)
	{
		if (r == nullptr || camera == nullptr)
		{
			return;
		}

		r->x -= camera->x;
		r->y -= camera->y;
	}

	void Context::setCamera(Camera* c)
	{
		camera = c;
	}

	Camera* Context::getCamera()
	{
		return camera;
	}
}
