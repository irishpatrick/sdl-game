#include "config.h"

int Config::SCREENWIDTH = 0;
int Config::SCREENHEIGHT = 0;
std::string Config::ASSETPATH = "";

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

void Config::load(const std::string& fn)
{
	std::ifstream t(fn);
	std::string data((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	json.Parse(data.c_str());

	if (json.HasMember("screenWidth"))
	{
		Config::SCREENWIDTH = json["screenWidth"].GetInt();
	}
	if (json.HasMember("screenHeight"))
	{
		Config::SCREENHEIGHT = json["screenHeight"].GetInt();
	}
	if (json.HasMember("assetPath"))
	{
		Config::ASSETPATH = json["assetPath"].GetString();
	}
}