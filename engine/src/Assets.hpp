#pragma once

#include "core_api.hpp"
#include <map>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace engine
{
	class Context;
	class Texture;

	class Assets
	{
	public:
		CORE_API static void loadTexture(Context& ctx, const std::string&);
		CORE_API static void loadTexturesFromVector(const std::string&, std::vector<std::string>, Context&);
		CORE_API static void loadTexturesFromJson(Context&, const std::string&);
		CORE_API static Texture* getTexture(const std::string&);
		CORE_API static void destroy();
        CORE_API static void registerTexture(Context&, Texture&, const std::string&);
        CORE_API static void registerTexture(Context&, Texture*, const std::string&);
		CORE_API static void useAll(Context&);
		CORE_API static void setCwd(const std::string&);
		CORE_API static void setCwd(fs::path);

	private:
		CORE_API static std::vector<std::string> split(const std::string&, char);
		CORE_API static std::map<std::string, Texture*> texMap;
		CORE_API static Texture* missing;
		CORE_API static fs::path cwd;
	};
}
