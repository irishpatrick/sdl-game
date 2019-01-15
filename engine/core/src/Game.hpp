#pragma once

#include "core_api.hpp"

namespace engine
{
	class Game
	{
	public:
		CORE_API Game();
		CORE_API ~Game();

	protected:
		bool running;
	};
}