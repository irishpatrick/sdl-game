#include "game.h"
#include "plane.h"

double deg(double r)
{
    return r * (M_PI / 180.0);
}

double rad(double d)
{
    return d * (180.0 / M_PI);
}

Game::Game(SDL_Renderer* r): State(r)
{
    plane = new Plane();
}

Game::~Game()
{
    delete plane;
}

void Game::init()
{
    std::string textures = "../assets/textures";
    Assets::loadTexture(textures + "plane.png", renderer);

    plane->setTexture(Assets::getTexture("plane.png"));
}

void Game::update(float delta, const uint8_t* keys)
{
    bool a = keys[SDL_SCANCODE_A];
    bool d = keys[SDL_SCANCODE_D];

    if (a)
    {
        plane->angle += rad(30) * delta;
    }
    if (d)
    {
        plane->angle -= rad(30) * delta;
    }
}

void Game::render()
{

}

void Game::destroy()
{

}
