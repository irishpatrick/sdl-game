#pragma once

#include "core_api.hpp"
#include "texture.hpp"
#include "sprite.hpp"
#include "context.hpp"
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
	} Anim;

	class KeyFrameSprite : public Sprite
	{
	public:
		KeyFrameSprite() : Sprite()
		{
			// dynamically allocated 
			animations = nullptr;
			frameRef = nullptr;

			currentAnim = -1;
			currentFrame = nullptr;
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

		CORE_API void init(Context& ctx, const std::string&);

	private:
		Anim* animations;
		Frame* frameRef;
		int currentAnim;
		Frame* currentFrame;
	};
}