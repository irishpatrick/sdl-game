#ifndef CONFIG_H
#define CONFIG_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <streambuf>
#include <rapidjson/document.h>

class Config
{
public:
    Config();
    ~Config();

    void load(const std::string&);

	static int screenwidth();
	static int screenheight();
	static std::string assetpath();

private:
    rapidjson::Document json;
	static int SCREENWIDTH;
	static int SCREENHEIGHT;
	static std::string ASSETPATH;
};

#endif /* CONFIG_H */