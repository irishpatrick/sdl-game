#pragma once

#include <engine.hpp>

#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <streambuf>
#include <nlohmann/json.hpp>
#include <experimental/filesystem>

using json = nlohmann::json;
namespace fs = std::experimental::filesystem;

class Config 
{
	public:
		static int load(const std::string&);

		static int getScreenWidth();
		static int getScreenHeight();
		static fs::path getAssetPath();
		static bool getFullscreen();

	private:
		static int screenWidth;
		static int screenHeight;
		static fs::path assetPath;
		static bool fullscreen;
};
