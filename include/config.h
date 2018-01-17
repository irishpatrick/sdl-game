#ifndef CONFIG_H
#define CONFIG_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <streambuf>
#include <json.hpp>

class Config
{
public:
    static void load(const std::string&);

	static int screenwidth();
	static int screenheight();
	static std::string assetpath();
	static bool fullscreen();

private:
	static int SCREENWIDTH;
	static int SCREENHEIGHT;
	static std::string ASSETPATH;
	static bool FULLSCREEN;
};

#endif /* CONFIG_H */