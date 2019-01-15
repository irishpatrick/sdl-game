#include "App.hpp"

App::App()
{

}

App::~App()
{

}

void App::init()
{
	ctx.init(512, 480, "title", false);
	running = true;
}

void App::update()
{

}

void App::render()
{

}

void App::mainLoop()
{
	while (running)
	{
		update();
		render();
	}
}