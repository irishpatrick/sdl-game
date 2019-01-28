#pragma once

#include "core_api.hpp"
#include "Context.hpp"

namespace engine
{
	class Game
	{
	public:
		CORE_API Game();
		CORE_API ~Game();

		CORE_API virtual void draw();
		CORE_API virtual void mainLoop();
		CORE_API void attachContext(Context&);
		CORE_API Context* getContext();
		CORE_API void quit();

	protected:
		bool running;
		Context* ctx;
	};
}