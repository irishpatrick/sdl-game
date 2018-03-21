#ifndef CONFIG_H
#define CONFIG_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <streambuf>
#include "nlohmann/json.hpp"
#include <engine.h>

using namespace std;
using json = nlohmann::json;

class Config
{
public:
    static void load(const string&);

	static int screenwidth();
	static int screenheight();
	static string assetpath();
	static bool fullscreen();

private:
	static int SCREENWIDTH;
	static int SCREENHEIGHT;
	static string ASSETPATH;
	static bool FULLSCREEN;
};

#endif /* CONFIG_H */
