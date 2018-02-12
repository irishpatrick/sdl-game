#include "game.h"
#include "plane.h"

double rad(double r)
{
    return r * (M_PI / 180.0);
}

double deg(double d)
{
    return d * (180.0 / M_PI);
}

Game::Game(SDL_Renderer* r): State(r)
{
    plane = new Plane();
    camera = new Camera();
    bg = new Plane();
    mx = 0;
    my = 0;
}

Game::~Game()
{
    delete bg;
    delete plane;
    delete camera;
}

void Game::setMousePos(int x, int y)
{
    mx = x;
    my = y;
}

void Game::init()
{
    std::string textures = "../../missiles/assets/textures/";
    Assets::loadTexture(textures + "plane.png", renderer);
    Assets::loadTexture(textures + "test-bg.png", renderer);

    Assets::getFutures();

    plane->setTexture(Assets::getTexture("plane.png"));
    plane->pos(640 / 2 + 32, 480 / 2 + 32);
    plane->setCamera(camera);
    plane->queryTexture();

    bg->setTexture(Assets::getTexture("test-bg.png"));
    bg->queryTexture();
    bg->setCamera(camera);

    camera->setFocus(plane);
    camera->screen(640, 480);
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

    if (mx - plane->x == 0)
    {

    }

    int x = mx - (640 / 2 + 32);
    int y = my - (480 / 2 + 32);
    if (x > 0)
    {
        plane->angle = deg(atan((float)x / (float)y));
    }
    else if (x < 0)
    {
        plane->angle = deg(-atan((float)x / (float)y));
    }

    //printf("%d, %d\n", mx, my);

    plane->xvel += (sin(rad(plane->angle)) * plane->thrust);
    plane->yvel += (-cos(rad(plane->angle)) * plane->thrust);

    plane->xvel -= (plane->xvel/50);
    plane->yvel -= (plane->yvel/50);

    /*if (plane->xvel > plane->max_speed)
    {
        plane->xvel = plane->max_speed;
    }
    else if (plane->xvel < -plane->max_speed)
    {
        plane->xvel = -plane->max_speed;
    }
    if (plane->yvel > plane->max_speed)
    {
        plane->yvel = plane->max_speed;
    }
    else if (plane->yvel < -plane->max_speed)
    {
        plane->yvel = -plane->max_speed;
    }*/

    //printf("x: %f y: %f\n", plane->xvel, plane->yvel);
    //printf("thrust: %f\n", plane->thrust);

    plane->update(delta);
    bg->update(delta);
    camera->update(delta);
}

void Game::render()
{
    bg->draw(renderer);
    plane->draw(renderer);
}

void Game::destroy()
{

}
