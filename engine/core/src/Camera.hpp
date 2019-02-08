#pragma once

#include "core_api.hpp"

namespace engine
{

class Sprite;

	class Camera
	{
	public:
		CORE_API Camera();
		CORE_API ~Camera();

		CORE_API void setFocus(Sprite*);
		CORE_API void update(float);
		CORE_API void setScreen(int, int);

		float x;
		float y;
	private:
		int w;
		int h;
		float fx;
		float fy;
		
		bool dynamic;
		Sprite* focus;
	};

}
