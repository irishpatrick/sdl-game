#include "game.h"

Game::Game(SDL_Renderer* r): State(r)
{

}

Game::~Game()
{
    testroom.destroy();
}

void Game::init()
{
    int w = 1920;
    int h = 1080;
    printf("loading assets\n");

    std::string textures = Config::assetpath() + "textures/";
    std::string maps = Config::assetpath() + "maps/";
    std::string root = Config::assetpath();
    std::string sprites = Config::assetpath() + "sprites/";

    Assets::loadTexture(textures + "med-background.png", renderer);
    Assets::loadTexture(textures + "hero.png", renderer);
    Assets::loadTexture(textures + "monster.png", renderer);
    Assets::loadTexture(textures + "grass1.png", renderer);
    Assets::loadTexture(textures + "room-bg.png", renderer);
    Assets::loadTexture(textures + "opposite.png", renderer);
    Assets::loadTexture(textures + "animtest.png", renderer);
    Assets::loadTexture(textures + "door.png", renderer);

    camera.screen(w, h);
    camera.setFocus(&hero);

    hero.setTexture(Assets::getTexture("hero.png"));

    hero.speed = 250.0f;

    monster.setTexture(Assets::getTexture("monster.png"));
    monster.pos(150, 150);

    background.setTexture(Assets::getTexture("med-background.png"));
    background.name = "background";

    light.x = 60;
    light.y = 60;
    light.size = 300;
    light.settexture(Assets::getTexture("opposite.png"));

    doortest.x = 500;
    doortest.y = 500;
    doortest.setTexture(Assets::getTexture("door.png"));
    doortest.SetManager(&groups_);
    doortest.SetDest("room");

    stage.add(&background);
    stage.add(&monster);
    stage.add(&hero);
    stage.add(&doortest);

    stage.sx = 300;
    stage.sy = 300;

    stage.setCamera(&camera);

    Assets::getFutures();

    light.querytexture();
    hero.queryTexture();
    monster.queryTexture();
    background.queryTexture();
    doortest.queryTexture();

    hero.pos((w / 2) - (hero.w / 2), (h / 2) - (hero.h / 2));

    //testroom.init_from_json(maps + "testroom.json");

    groups_.setcamera(&camera);
    groups_.setfocus(&hero);
    groups_.loadgroup("room", maps + "testroom.json");
    groups_.addgroup("stage", &stage);
    //groups_.addgroup("room", &testroom);
    groups_.setactive("stage");
    //groups_.setactive("room");

    printf("done!\n");

    printf("starting tests...\n");

    //test.InitFromJson(root + "animtest.json");
    animtest.InitAnimation(sprites + "animtest.json");
    animtest.GetAnimation()->Start("all", true);
    stage.add(&animtest);

    printf("done!\n");
}

void Game::update(float delta, const uint8_t* keys)
{
    bool w = keys[SDL_SCANCODE_W];
    bool s = keys[SDL_SCANCODE_S];
    bool a = keys[SDL_SCANCODE_A];
    bool d = keys[SDL_SCANCODE_D];
    bool r = keys[SDL_SCANCODE_R];
    bool p = keys[SDL_SCANCODE_P];
    bool l = keys[SDL_SCANCODE_L];
    //bool up = keys[SDL_SCANCODE_UP];
    //bool down = keys[SDL_SCANCODE_DOWN];
    //bool left = keys[SDL_SCANCODE_LEFT];
    //bool right = keys[SDL_SCANCODE_RIGHT];

    if (r)
    {
        groups_.setactive("room");
    }

    if ((w || s) && (a || d))
    {
        float v = sqrt(pow(hero.speed, 2) / 2.0);
        hero.xvel = v;
        hero.yvel = v;
    }
    else
    {
        hero.xvel = hero.speed;
        hero.yvel = hero.speed;
    }

    if (w)
    {
        hero.y -= hero.yvel * delta;
    }
    if (s)
    {
        hero.y += hero.yvel * delta;
    }
    if (a)
    {
        hero.x -= hero.xvel * delta;
    }
    if (d)
    {
        hero.x += hero.xvel * delta;
    }

    if (p)
    {
        Sprite* collider = hero.GetCollision();
        if (collider != nullptr)
        {
            if (Door* d = dynamic_cast<Door*>(collider))
            {
                // success
                d->Enter();
            }
        }
    }

    std::vector<Sprite*>::iterator it;
    std::vector<Sprite*> list = groups_.getactive()->getSprites();
    for (it = list.begin(); it != list.end(); it++)
    {
        Sprite* current = *it;
        if (hero.getUUID() == current->getUUID())
        {
            continue;
        }
        if (background.getUUID() == current->getUUID())
        {
            continue;
        }

        const std::string result = Util::checkCollision(&hero, current);
        if (result == "north")
        {
            hero.y += hero.yvel * delta;
        }
        if (result == "south")
        {
            hero.y -= hero.yvel * delta;
        }
        if (result == "east")
        {
            hero.x -= hero.xvel * delta;
        }
        if (result == "west")
        {
            hero.x += hero.xvel * delta;
        }
    }

    animtest.update(delta);

    Util::contain(&hero, groups_.getactive()->get_sprite_by_name("background"));

    camera.update(delta);

    groups_.getactive()->sort();

    //printf("%f,%f - %f,%f\n", hero.x, hero.y, background.x, background.y);
    /*printf("%x, %x, %x\n",
        hero.texture->use(),
        monster.texture->use(),
        background.texture->use());*/
}

void Game::render()
{
    groups_.getactive()->draw(renderer);
    //light.draw(renderer);
}

void Game::destroy()
{
    Assets::destroy();
    for (auto &e : grass)
    {
        delete e;
    }
}
