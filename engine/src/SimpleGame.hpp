#pragma once

#include "core_api.hpp"
#include "Game.hpp"

namespace engine
{
	class SimpleGame : public Game
	{
	public:
		CORE_API SimpleGame();
		CORE_API virtual ~SimpleGame();
	};
}
