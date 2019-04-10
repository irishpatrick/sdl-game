#include "App.hpp"
#include "Util.hpp"
#include "Mouse.hpp"
#include <cstdint>
#include <cstdlib>

int App::running = 1;

void App::quitCallback()
{
    running = 0;
}

void App::testCallback()
{
    printf("test button\n");
}

App::App() : SimpleGame()
{

}

App::~App()
{

}

void App::init()
{
    ctx.init(1024, 768, "Editor", false);
    printf("sanity check: %d, %d\n", ctx.getWidth(), ctx.getHeight());
    ctx.setQuitCallback(this->quitCallback);
    Mouse::setScale(ctx.getScale());
    
    engine::Assets::loadTexture(ctx, "assets/test.png");

    test.init(ctx);
    test.setToggle(1);
    test.setTexture(engine::Assets::getTexture("test.png"));
    Pointf pf = {-0.4f, 0.4f};
    Point p = Util::toPixelSpace(&pf, &ctx);
    test.x = p.x;
    test.y = p.y;
    test.setClickCallback(this->testCallback);
}

void App::update()
{
    ctx.pollEvents();
    const uint8_t* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_ESCAPE])
    {
        running = 0;
    }

    Mouse::poll();

    test.update(0.1f);
}

void App::draw()
{
    ctx.clear();
	
    test.draw(ctx);
    
    ctx.render();
}

void App::mainLoop()
{
    init();
    running = 1;
    while (running)
    {
        update();
        draw();
    }
}