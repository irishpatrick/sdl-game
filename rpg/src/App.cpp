#include "App.hpp"
#include "Config.hpp"

App::App()
{

}

App::~App()
{

}

void App::init()
{
	#ifdef _WIN32
		Config::load((fs::current_path() / fs::path("assets/config-win.json")).generic_string());
	#elif __linux__
		Config::load((fs::current_path() / fs::path("assets/config.json")).generic_string());
	#endif
	
	int result = ctx.init(Config::getScreenWidth(), Config::getScreenHeight(), "title", false);
	if (result < 0) std::exit(-1);
	addState("game", &game);
	addState("title", &title);
	setCurrentState("game");
}