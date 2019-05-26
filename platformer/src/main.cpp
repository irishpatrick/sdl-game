#include <iostream>
#include "App.hpp"

int main(int argc, char** argv)
{
	std::cout << "hello world" << std::endl;
	App app;
	app.mainLoop();

	return 0;
}