#pragma once

#include "core_api.hpp"

#include <cstdint>
#include <SDL2/SDL.h>

#include "context.hpp"

namespace engine {

	class State {
	public:
		CORE_API State();
		CORE_API virtual ~State();
		
		CORE_API virtual void init(Context&);
		CORE_API virtual void update(float, const uint8_t*);
		CORE_API virtual void render(Context&);

		CORE_API virtual void destroy();

	};

}
