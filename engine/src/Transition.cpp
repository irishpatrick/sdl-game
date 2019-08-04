#include "Transition.hpp"
#include "Util.hpp"
#include "Context.hpp"
#include "Clock.hpp"
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

namespace engine
{

	Transition::Transition()
	{
		alpha = 0;
		duration = 0;
		running = false;
		status = 0;
	}

	Transition::~Transition()
	{

	}

	void Transition::setAlpha(uint8_t a)
	{
		alpha = a;
	}

	void Transition::blockingFadeOut(Context* ctx, uint32_t d)
	{
		if (!running)
		{
			fadeOut(d);
		}
		while (running)
		{
			update();
			draw(ctx);
		}
	}

	void Transition::blockingFadeIn(Context* ctx, uint32_t d)
	{
		if (!running)
		{
			fadeIn(d);
		}
		while (running)
		{
			update();
			draw(ctx);
		}
	}

	void Transition::fadeOut(uint32_t d)
	{
		status = false;
		if (!running)
		{
			running = true;
			duration = (double)(d * 1e6);
			start = Clock::getNano();
			fade = FADE_OUT;
			timer.start();
		}
	}

	void Transition::fadeIn(uint32_t d)
	{
		status = false;
		if (!running)
		{
			running = true;
			duration = (double)(d * 1e6);
			start = Clock::getNano();
			fade = FADE_IN;
			timer.start();
		}
	}

	void Transition::fill(Context* ctx, uint8_t a)
	{
		SDL_SetRenderDrawBlendMode(ctx->getRenderer(), SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(ctx->getRenderer(), 0, 0, 0, a);
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = ctx->getWidth();
		rect.h = ctx->getHeight();
		SDL_RenderFillRect(ctx->getRenderer(), &rect);
		SDL_SetRenderDrawColor(ctx->getRenderer(), 0, 0, 0, 255);
	}

	void Transition::update()
	{
		if (running)
		{
			//std::cout << "running transition ";
			long delta = timer.getElapsed();
			float t = (float)delta / (float)(duration);
			//std::cout << "t=" << t << std::endl;
			if (t >= 1.0f)
			{
				running = false;
				status = 1;
				t = 1.0f;
			}
			float lerp = 0.0f;
			if (fade == FADE_OUT)
			{
				lerp = Util::lerp(t, 0.0f, 255.0f);
			}
			else if (fade == FADE_IN)
			{
				lerp = Util::lerp(t, 255.0f, 0.0f);
			}
			alpha = (uint8_t)lerp;
		}
	}
}
