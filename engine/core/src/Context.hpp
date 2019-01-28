#pragma once

#include "core_api.hpp"

#include <string>
#include <SDL.h>

namespace engine
{

	class Context 
	{

	public:
		CORE_API Context();
		CORE_API ~Context();

		CORE_API int init(int, int, const std::string&, bool);

		CORE_API inline int getWidth() 
		{
			return width;
		}

		CORE_API inline int getHeight()
		{
			return height;
		}

		CORE_API inline SDL_Window* getWindow()
		{
			return w;
		}

		CORE_API inline SDL_Renderer* getRenderer()
		{
			return r;
		}

		CORE_API inline void clear()
		{
			SDL_RenderClear(r);
		}

		CORE_API inline void render()
		{
			SDL_RenderPresent(r);
		}

		CORE_API inline void destroy()
		{
			SDL_DestroyRenderer(r);
			SDL_DestroyWindow(w);
			SDL_Quit();
		}

		CORE_API inline float coordX(float x)
		{
			return (0.5f * x * width) + (width / 2.0f);
		}

		CORE_API inline float coordY(float y)
		{
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
