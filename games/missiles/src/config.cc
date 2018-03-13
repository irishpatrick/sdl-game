#include "config.h"

json Config::o = json();

void Config::loadFile(const std::string& fn)
{
    std::ifstream i(fn);
    if (!i)
    {
    	printf("failed to open %s\n", fn.c_str());
    	exit(1);
    }
    i >> o;
}

int Config::getScreenWidth()
{
    if (o.find("screen_width") != o.end())
    {
        return (int)o["screen_width"];
    }
    return -1;
}

int Config::getScreenHeight()
{
    if (o.find("screen_height") != o.end())
    {
        return (int)o["screen_height"];
    }
    return -1;
}

std::string Config::getAssetPath()
{
    if (o.find("asset_path") != o.end())
    {
        return o["asset_path"];
    }
    return "";
}

int Config::getDrag()
{
    if (o.find("drag") != o.end())
    {
        return o["drag"];
    }
    return -1;
}

int Config::getPlaneSpeed()
{
    if (o.find("plane_speed") != o.end())
    {
        return o["plane_speed"];
    }
    return -1;
}

int Config::getMissileAcceleration()
{
    if (o.find("missile_acceleration") != o.end())
    {
        return o["missile_acceleration"];
    }
    return -1;
}
