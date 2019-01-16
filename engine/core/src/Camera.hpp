#pragma once

#include "core_api.hpp"
#include "Object.hpp"

namespace engine
{

class Sprite;

	class Camera : public Object
	{
	public:
		CORE_API Camera();
		CORE_API ~Camera();

		CORE_API void setFocus(Sprite*);
		CORE_API void update(float);
		CORE_API void setScreen(int, int);

	private:
		int w;
		int h;
		float fx;
		float fy;
		Sprite* focus;
	};

}
