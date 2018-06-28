#include "config.hpp"
#include <SDL2/SDL.h>

int Config::screenWidth = 0;
int Config::screenHeight = 0;
string Config::assetPath = string();
bool Config::fullscreen = false;

int Config::getScreenWidth()
{
    return screenWidth;
}

int Config::getScreenHeight()
{
    return screenHeight;
}

std::string Config::getAssetPath()
{
    return assetPath;
}

bool Config::getFullscreen()
{
    return fullscreen;
}

int Config::load(const string& fn)
{
    ifstream i(fn);
    if (!i)
    {
    	printf("failed to open %s\n", fn.c_str());
    	SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Error",
            "Failed to load config",
            nullptr
        );
        exit(1);
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
    	assetPath = o["assetPath"];
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
}
