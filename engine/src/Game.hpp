#pragma once

#include "core_api.hpp"
#include "Context.hpp"

namespace engine
{
	class Game
	{
	public:
		CORE_API Game();
		CORE_API virtual ~Game();

		CORE_API virtual void draw();
		CORE_API virtual void mainLoop();

	};
}
