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

    string textures = Config::assetpath() + "textures/";
    string maps = Config::assetpath() + "maps/";
    string root = Config::assetpath();
    string sprites = Config::assetpath() + "sprites/";

    engine::Assets::loadTexture(textures + "med-background.png", renderer);
    engine::Assets::loadTexture(textures + "hero.png", renderer);
    engine::Assets::loadTexture(textures + "monster.png", renderer);
    engine::Assets::loadTexture(textures + "grass1.png", renderer);
    engine::Assets::loadTexture(textures + "room-bg.png", renderer);
    engine::Assets::loadTexture(textures + "opposite.png", renderer);
    engine::Assets::loadTexture(textures + "animtest.png", renderer);
    engine::Assets::loadTexture(textures + "door.png", renderer);
    camera.screen(w, h);
    camera.setFocus(&hero);

    hero.setTexture(engine::Assets::getTexture("hero.png"));
    hero.name = "hero";
    hero.speed = 250.0f;

    monster.setTexture(engine::Assets::getTexture("monster.png"));
    monster.pos(150, 150);
    monster.name = "monster";

    background.setTexture(engine::Assets::getTexture("med-background.png"));
    background.name = "background";
    background.solid = false;

    light.x = 60;
    light.y = 60;
    light.size = 300;
    light.settexture(engine::Assets::getTexture("opposite.png"));

    doortest.x = 500;
    doortest.y = 500;
    doortest.name = "door";
    doortest.setTexture(engine::Assets::getTexture("door.png"));
    doortest.SetManager(&groups_);
    doortest.SetDest("room");

    stage.add(&background);
    stage.add(&monster);
    stage.add(&hero);
    stage.add(&doortest);

    stage.sx = 300;
    stage.sy = 300;

    stage.setCamera(&camera);

    engine::Assets::getFutures();

    light.querytexture();
    hero.queryTexture();
    monster.queryTexture();
    background.queryTexture();
    doortest.queryTexture();

    //hero.pos((w / 2) - (hero.w / 2), (h / 2) - (hero.h / 2));
    hero.pos(10,10);

    //testroom.init_from_json(maps + "testroom.json");

    groups_.setcamera(&camera);
    groups_.setfocus(&hero);
    groups_.loadgroup("room", maps + "testroom.json");
    groups_.loadgroup("town1", maps + "town1.json");
    groups_.addgroup("stage", &stage);
    groups_.setactive("town1");
    printf("done!\n");

    //test.InitFromJson(root + "animtest.json");
    animtest.InitAnimation(sprites + "animtest.json");
    animtest.GetAnimation()->Start("all", true);
    stage.add(&animtest);

    //engine.LoadEffect(root + "particles.json");

    tests();

    hero_collisions = engine::Util::GetCollisions(&hero, groups_.getactive());
}

void Game::tests()
{
    printf("starting tests...\n");

    /*text.setText("hello world!  this is going to be a very long string with the purpose of demonstrating the functionality of the text.cc class!");
    text.x = 400;
    text.y = 400;
    text.setSpeed(20);

    othr.setText("I am writing a very long string to this class in order to try to replicate the bug that currently resides in the text.cc class!");
    othr.pos(500,500);*/

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
    //bool l = keys[SDL_SCANCODE_L];
    //bool up = keys[SDL_SCANCODE_UP];
    //bool down = keys[SDL_SCANCODE_DOWN];
    //bool left = keys[SDL_SCANCODE_LEFT];
    //bool right = keys[SDL_SCANCODE_RIGHT];

    //printf("%d\n", hero_collisions.size());

    if (r)
    {
        groups_.setactive("room");
    }

    if ((w || s) && (a || d))
    {
        hero_collisions = engine::Util::GetCollisions(&hero, groups_.getactive());
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

    if ((w || s) || (a || d))
    {
        hero_collisions = engine::Util::GetCollisions(&hero, groups_.getactive());
    }

    //hero_collisions = Util::GetCollisions(&hero, groups_.getactive());

    op.check(p);
    if (op.fire())
    {
        if (hero_collisions.size() > 0)
        {
            engine::Sprite* collider = hero_collisions[0];
            if (Door* d = dynamic_cast<Door*>(collider))
            {
                // success
                //printf("entering door!\n");
                //hero.pos(d->GetExit()->x, d->GetExit()->y);
                //d->SetExit(hero.x, hero.y);
                if (!hero.getDoorStack()->isEmpty())
                {
                    //printf("stack not empty!\n");
                    engine::Point pos = hero.getDoorStack()->pop();
                    printf("popped %f, %f\n", pos.x, pos.y);
                    hero.x = pos.x;
                    hero.y = pos.y;
                }
                else
                {
                    hero.getDoorStack()->push(*d->GetExit());
                }
                //hero.ResetCollision();

                d->Enter();
            }
        }
    }

    vector<engine::Sprite*>::iterator it;
    vector<engine::Sprite*> list = groups_.getactive()->getSprites();
    for (it = list.begin(); it != list.end(); it++)
    {
        engine::Sprite* current = *it;
        if (hero.getUUID() == current->getUUID())
        {
            continue;
        }
        if (background.getUUID() == current->getUUID())
        {
            continue;
        }

        const string result = engine::Util::checkCollision(&hero, current);
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

    engine::Util::contain(&hero, groups_.getactive()->get_sprite_by_name("background"));

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
    //othr.staticDraw(renderer);
    //light.draw(renderer);
}

void Game::destroy()
{
    engine::Assets::destroy();
    for (auto &e : grass)
    {
        delete e;
    }
}
