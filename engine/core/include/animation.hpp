#pragma once

#include "core_api.hpp"

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace engine {

	class Texture;
	class Timer;

	typedef struct {
		char* name;
		uint32_t fps;
		uint32_t count;
		uint32_t* frames;
	} FrameSet;

	class Animation
	{
	public:
		CORE_API Animation();
		CORE_API ~Animation();

		CORE_API void initFromJson(const std::string&);
		CORE_API void Start(const std::string&, bool);
		CORE_API void Update();
		CORE_API void Stop();
		CORE_API void Kill();
		CORE_API SDL_Rect* GetCurrentFrame();
		CORE_API Texture* GetTexture();
		CORE_API uint32_t GetFrameWidth();
		CORE_API uint32_t GetFrameHeight();

	private:
		//std::map<std::string, FrameSet> animmap_;
		std::vector<FrameSet*> animations_;
		SDL_Rect* currentframe_;
		uint32_t currentindex_;
		FrameSet* currentset_;
		std::vector<SDL_Rect*> frames_;
		Texture* tex_;
		Timer* timer_;
		bool running_;
		bool looping_;
		uint32_t framewidth_;
		uint32_t frameheight_;
	};

}
