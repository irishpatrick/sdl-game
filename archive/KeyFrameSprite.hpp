#pragma once

#include "Sprite.hpp"
#include "Texture.hpp"
#include "Timer.hpp"
#include <string>
#include <vector>

namespace engine
{
	typedef struct _Frame
	{
        float x;
		float y;
		int w;
		int h;
	} Frame;

	typedef struct _Anim
	{
		int fps;
		int length;
		int* frames;
		char* name;
	} Anim;

	class KeyFrameSprite : public Sprite
	{
	public:
		KeyFrameSprite() : Sprite()
		{
			// dynamically allocated

			//animations = nullptr;
			//frameRef = nullptr;
			numAnimations = -1;

			currentAnim = -1;
			currentFrame = 0;
			running = true;
			initialized = false;
		}

		~KeyFrameSprite()
		{}

        using Sprite::init;
		CORE_API void init(Context&, const std::string&);
		CORE_API void setCurrentAnimation(const std::string&, bool);
        CORE_API void setCurrentFrame(int);
		CORE_API void update(float);
        CORE_API void update();
		CORE_API void draw(Context&);
		CORE_API void draw(Context&, float);
		CORE_API void draw(Context& , float, Point);
		CORE_API void stop();

	private:
		std::vector<Anim> animations;
		std::vector<Frame> frames;
		int currentAnim;
		int numAnimations;
		int currentFrame;
		int frameIndex;
		Timer timer;
		bool running;
		bool repeat;
		bool frameCount;
		bool initialized;
	};
}
