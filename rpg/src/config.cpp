#include "config.hpp"
#include <SDL2/SDL.h>

int Config::screenWidth = 0;
int Config::screenHeight = 0;
//std::string Config::assetPath = std::string();
fs::path Config::assetPath = fs::current_path();
bool Config::fullscreen = false;

int Config::getScreenWidth()
{
    return screenWidth;
}

int Config::getScreenHeight()
{
    return screenHeight;
}

fs::path Config::getAssetPath()
{
    return assetPath;
}

bool Config::getFullscreen()
{
    return fullscreen;
}

int Config::load(const std::string& fn)
{
    std::ifstream i(fn);
    if (!i)
    {
    	printf("failed to open %s\n", fn.c_str());
    	SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Error",
            "Failed to load config",
            nullptr
        );
        //exit(1);
        return 1;
    }
    json o;
    i >> o;

    if (engine::Util::JsonExists(o, "screenWidth"))
    {
    	screenWidth = o["screenWidth"];
    }
    if (engine::Util::JsonExists(o, "screenHeight"))
    {
    	screenHeight = o["screenHeight"];
    }
    if (engine::Util::JsonExists(o, "assetPath"))
    {
		// separate to resolve strange error
		std::string str = o["assetPath"];
		assetPath = fs::path(str);
    }
    if (engine::Util::JsonExists(o, "fullscreen"))
    {
    	int res = o["fullscreen"];
    	if (res == 1)
    	{
    		fullscreen = true;
    	}
    	else if (res == 0)
    	{
    		fullscreen = false;
    	}
    }
    return 0;
}
