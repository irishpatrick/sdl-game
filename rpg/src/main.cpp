#include <iostream>
#include "App.hpp"

#ifdef main
#undef main
#endif
int main() {
    std::cout << "hello, world!" << std::endl;
    
    App app;
    app.init();
	app.draw();

    return 0;
}
