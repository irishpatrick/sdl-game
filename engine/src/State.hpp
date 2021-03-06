#pragma once

#include "core_api.hpp"
#include <cstdint>
#include <SDL.h>
#include "Context.hpp"
#include "Game.hpp"
#include <string>

namespace engine
{
	class State
	{
	public:
		CORE_API State();
		CORE_API virtual ~State();

		CORE_API virtual void onEntry();
		CORE_API virtual void init(Context&);
		CORE_API virtual void update();
		CORE_API virtual void update(float);
		CORE_API virtual void render(Context&);
		CORE_API virtual void render(Context&, float);
		virtual void render();
		virtual void render(float);
		CORE_API void updateKeys();
		CORE_API virtual void destroy();
		CORE_API void setGame(Game&);
		
		void setName(const std::string&);
		std::string getName();

	protected:
		std::string name;
		uint8_t* kbd;
		Game* game;
	};
}
