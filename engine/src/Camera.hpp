#pragma once

#include "core_api.hpp"
#include "BoundingBox.hpp"

namespace engine
{

class Sprite;

	class Camera
	{
	public:
		CORE_API Camera();
		CORE_API ~Camera();

		CORE_API virtual void setFocus(Sprite*);
		CORE_API virtual void update();
		CORE_API void setScreen(int, int);
        CORE_API BoundingBox getViewport();

		float x;
		float y;
	private:
		int w;
		int h;

		bool dynamic;
		Sprite* focus;
	};

}
