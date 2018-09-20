#pragma once

#include "core_api.hpp"
#include "texture.hpp"
#include "sprite.hpp"
#include "context.hpp"
#include "timer.hpp"
#include <string>

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
			animations = nullptr;
			frameRef = nullptr;
			numAnimations = 0;

			currentAnim = -1;
			currentFrame = 0;
		}

		~KeyFrameSprite()
		{
			if (animations != nullptr)
			{
				free(animations);
			}
			if (frameRef != nullptr)
			{
				free(frameRef);
			}
		}

		CORE_API void init(Context&, const std::string&);
		CORE_API void setCurrentAnimation(const std::string&);
		CORE_API void update(float);
		CORE_API void draw(Context&);

	private:
		Anim* animations;
		Frame* frameRef;
		int currentAnim;
		int numAnimations;
		int currentFrame;
		Timer timer;
	};
}