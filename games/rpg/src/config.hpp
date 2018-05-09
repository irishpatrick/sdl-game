#pragma once

#include <engine.h>

#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <streambuf>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class Config {
 public:
    static void load(const string&);

    static int getScreenWidth();
    static int getScreenHeight();
    static string getAssetPath();
    static bool getFullscreen();

 private:
    static int screenWidth;
    static int screenHeight;
    static string assetPath;
    static bool fullscreen;
};
