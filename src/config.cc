#include "config.h"
#include "util.h"

int Config::SCREENWIDTH = 0;
int Config::SCREENHEIGHT = 0;
std::string Config::ASSETPATH = "";
bool Config::FULLSCREEN = false;

int Config::screenwidth()
{
    return SCREENWIDTH;
}

int Config::screenheight()
{
    return SCREENHEIGHT;
}

std::string Config::assetpath()
{
    return ASSETPATH;
}

bool Config::fullscreen()
{
    return FULLSCREEN;
}

void Config::load(const std::string& fn)
{
    std::ifstream i(fn);
    if (!i)
    {
    	printf("failed to open %s\n", fn.c_str());
    	exit(1);
    }
    nlohmann::json o;
    i >> o;

    if (Util::JsonExists(o, "screenWidth"))
    {
    	SCREENWIDTH = o["screenWidth"];
    }
    if (Util::JsonExists(o, "screenHeight"))
    {
    	SCREENHEIGHT = o["screenHeight"];
    }
    if (Util::JsonExists(o, "assetPath"))
    {
    	ASSETPATH = o["assetPath"];
    }
    if (Util::JsonExists(o, "fullscreen"))
    {
    	int res = o["fullscreen"];
    	if (res == 1)
    	{
    		FULLSCREEN = true;
    	}
    	else if (res == 0)
    	{
    		FULLSCREEN = false;
    	}
    }
}
