#include <iostream>
#include "App.hpp"

int main()
{
    std::cout << "hello world" << std::endl;
    App app;
    app.init();
    app.draw();
    return 0;
}