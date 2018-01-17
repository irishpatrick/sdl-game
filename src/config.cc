#include "config.h"

int Config::SCREENWIDTH = 0;
int Config::SCREENHEIGHT = 0;
std::string Config::ASSETPATH = "";
bool Config::FULLSCREEN = false;

Config::Config()
{
    
}

Config::~Config()
{
    
}

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
	nlohmann::json o;
	i >> o;

	if (o.find("screenWidth") != o.end())
	{
		Config::SCREENWIDTH = o["screenWidth"];
	}
	if (o.find("screenHeight") != o.end())
	{
		Config::SCREENHEIGHT = o["screenHeight"];
	}
	if (o.find("assetPath") != o.end())
	{
		Config::ASSETPATH = o["assetPath"];
	}
	if (o.find("fullscreen") != o.end())
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