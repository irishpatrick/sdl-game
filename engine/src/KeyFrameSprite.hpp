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
			numAnimations = 0;

			currentAnim = -1;
			currentFrame = 0;
			running = true;
			initialized = false;
		}

		~KeyFrameSprite()
		{
			/*if (animations != nullptr)
			{
				free(animations);
			}
			if (frameRef != nullptr)
			{
				free(frameRef);
			}*/
		}

        using Sprite::init;
		CORE_API void init(Context&, const std::string&);
		CORE_API void setCurrentAnimation(const std::string&, bool);
		CORE_API void update(float);
		CORE_API void draw(Context&);
		CORE_API void stop();

	private:
		//Anim* animations;
		//Frame* frameRef;
		std::vector<Anim> animations;
		std::vector<Frame> frameRef;
		int currentAnim;
		int numAnimations;
		int currentFrame;
		Timer timer;
		bool running;
		bool repeat;
		bool frameCount;
		bool initialized;
	};
}
