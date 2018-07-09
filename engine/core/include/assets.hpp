#pragma once

#include "core_api.hpp"

#include <map>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

namespace engine {

	class Context;
	class Texture;

	class Assets {
	public:

		CORE_API static void loadTexture(const std::string&, Context& ctx);
		CORE_API static void loadTexturesFromVector(const std::string&, std::vector<std::string>, Context&);
		CORE_API static void loadTexturesFromJson(const std::string&, const std::string&, Context&);
		CORE_API static Texture* getTexture(const std::string&);
		CORE_API static void getMissingTexture(Context&);
		CORE_API static void destroy();
		//CORE_API static void getFutures();
		CORE_API static void useAll(Context&);

	private:
		//CORE_API static void single_load(Texture*, const std::string&);
		CORE_API static std::map<std::string, Texture*> texMap;
		CORE_API static Texture* missing;
	};
}
