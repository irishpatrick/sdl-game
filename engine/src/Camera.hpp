#pragma once

#include "core_api.hpp"
#include "BoundingBox.hpp"
#include "Context.hpp"

namespace engine
{

class Sprite;

	class Camera
	{
	public:
		CORE_API Camera();
		CORE_API ~Camera();

        CORE_API virtual void init(Context&);
		CORE_API virtual void setFocus(Sprite*);
        CORE_API virtual void setFocus(Sprite&);
		CORE_API virtual void update();
		CORE_API void setScreen(int, int);
        CORE_API BoundingBox getViewport();
		CORE_API void setMode(int);

		float x;
		float y;
        float xvel;
        float yvel;

		static const int LOCKED = 0;
		static const int FOLLOW = 1;
	protected:
		int mode;
		int w;
		int h;

		bool dynamic;
		Sprite* focus;
	};

}
