#include "config.h"

int Config::SCREENWIDTH = 0;
int Config::SCREENHEIGHT = 0;
string Config::ASSETPATH = "";
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

void Config::load(const string& fn)
{
    ifstream i(fn);
    if (!i)
    {
    	printf("failed to open %s\n", fn.c_str());
    	exit(1);
    }
    json o;
    i >> o;

    if (engine::Util::JsonExists(o, "screenWidth"))
    {
    	SCREENWIDTH = o["screenWidth"];
    }
    if (engine::Util::JsonExists(o, "screenHeight"))
    {
    	SCREENHEIGHT = o["screenHeight"];
    }
    if (engine::Util::JsonExists(o, "assetPath"))
    {
    	ASSETPATH = o["assetPath"];
    }
    if (engine::Util::JsonExists(o, "fullscreen"))
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
