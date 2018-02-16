#include "game.h"
#include "plane.h"
#include "missile.h"
#include "myutil.h"
#include "config.h"

Game::Game(SDL_Renderer* r): State(r)
{
    plane = new Plane();
    camera = new Camera();
    bg = new Plane();
    timer = new Timer();
    timer->SetInterval(5000);
    mx = 0;
    my = 0;
}

Game::~Game()
{
    delete bg;
    delete plane;
    delete camera;
    delete timer;
    for (auto& e : missiles)
    {
        delete e;
    }
}

void Game::setMousePos(int x, int y)
{
    mx = x;
    my = y;
}

void Game::init()
{
    std::string textures = Config::getAssetPath() + "textures/";
    Assets::loadTexture(textures + "plane.png", renderer);
    Assets::loadTexture(textures + "missile.png", renderer);
    Assets::loadTexture(textures + "test-bg.png", renderer);

    Assets::getFutures();

    plane->setTexture(Assets::getTexture("plane.png"));
    plane->pos(Config::getScreenWidth() / 2 + 32, Config::getScreenHeight() / 2 + 32);
    plane->setCamera(camera);

    bg->setTexture(Assets::getTexture("test-bg.png"));
    bg->setCamera(camera);

    camera->setFocus(plane);
    camera->screen(Config::getScreenWidth(), Config::getScreenHeight());
}

void Game::update(float delta, const uint8_t* keys)
{
    bool a = keys[SDL_SCANCODE_A];
    bool d = keys[SDL_SCANCODE_D];
    bool p = keys[SDL_SCANCODE_P];
    bool l = keys[SDL_SCANCODE_L];

    //plane->angle = 0;

    if (a)
    {
        plane->angle -= 160 * delta;
    }
    if (d)
    {
        plane->angle += 160 * delta;
    }

    float x = mx - (Config::getScreenWidth() / 2 + 32);
    float y = my - (Config::getScreenHeight() / 2 + 32);
    //float dist = sqrt(pow(x,2) + pow(y,2));

    if (x > 0)
    {
        plane->angle = MyUtil::deg(atan(y / x)) + 90;
    }
    else if (x < 0)
    {
        plane->angle = 270 + MyUtil::deg(atan(y / x));
    }
    else
    {
        if (y > 0)
        {
            plane->angle = 180;
        }
        if (y < 0)
        {
            plane->angle = 0;
        }
    }

    plane->xvel = (sin(MyUtil::rad(plane->angle)) * plane->max_speed);
    plane->yvel = (-cos(MyUtil::rad(plane->angle)) * plane->max_speed);
    /*plane->xvel -= (plane->xvel/Config::getDrag());
    plane->yvel -= (plane->yvel/Config::getDrag());*/

    if (timer->Tick())
    {
        printf("tick!\n");
        Missile* m = new Missile();
        m->setTexture(Assets::getTexture("missile.png"));
        m->setCamera(camera);
        m->setTarget(plane);
        m->launch();
        missiles.push_back(m);
    }

    for (auto& e: missiles)
    {
        e->update(delta);
    }

    plane->update(delta);
    bg->update(delta);
    camera->update(delta);

    for (auto& e: missiles)
    {
        if (MyUtil::checkCollision(plane, e))
        {
            printf("hit!\n");
        }
    }
}

void Game::render()
{
    bg->draw(renderer);
    plane->draw(renderer);
    for (auto& e: missiles)
    {
        e->draw(renderer);
    }
}

void Game::destroy()
{

}
