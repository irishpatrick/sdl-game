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
    printf("loading assets\n");

	std::string textures = Config::assetpath() + "textures/";
    std::string maps = Config::assetpath() + "maps/";

    assets.loadTexture(textures + "med-background.png", renderer);
    assets.loadTexture(textures + "hero.png", renderer);
    assets.loadTexture(textures + "monster.png", renderer);
	assets.loadTexture(textures + "grass1.png", renderer);
    assets.loadTexture(textures + "room-bg.png", renderer);
    assets.loadTexture(textures + "opposite.png", renderer);

    camera.screen(Config::screenwidth(), Config::screenheight());
    camera.setFocus(&hero);

    hero.setTexture(assets.getTexture("hero.png"));
    
    hero.speed = 250.0f;
    
    monster.setTexture(assets.getTexture("monster.png"));
    monster.pos(150, 150);

    background.setTexture(assets.getTexture("med-background.png"));
    background.name = "background";

    light.x = 60;
    light.y = 60;
    light.size = 300;
    light.settexture(assets.getTexture("opposite.png"));

    stage.add(&background);
    stage.add(&monster);
    stage.add(&hero);

    stage.sx = 300;
    stage.sy = 300;

    for (int i=0; i<500; i++)
    {
        Sprite* current = new Sprite();
        current->x = rand() % Config::screenwidth();
        current->y = rand() % Config::screenwidth();
        current->solid = false;
        current->setTexture(assets.getTexture("grass1.png"));
        stage.add(current);
        grass.push_back(current);
    }

    stage.setCamera(&camera);

    assets.getFutures();

    light.querytexture();

	hero.queryTexture();
	monster.queryTexture();
	background.queryTexture();

	hero.pos((Config::screenwidth() / 2) - (hero.w / 2), (Config::screenheight() / 2) - (hero.h / 2));

    //testroom.setassets(&assets);
    //testroom.init_from_json(maps + "testroom.json");

	groups_.setcamera(&camera);
    groups_.setassets(&assets);
	groups_.setfocus(&hero);
    groups_.loadgroup("room", maps + "testroom.json");
	groups_.addgroup("stage", &stage);
    //groups_.addgroup("room", &testroom);
	groups_.setactive("stage");
    //groups_.setactive("room");

    printf("done!\n");
}

void Game::update(float delta, const uint8_t* keys)
{
    bool w = keys[SDL_SCANCODE_W];
    bool s = keys[SDL_SCANCODE_S];
    bool a = keys[SDL_SCANCODE_A];
    bool d = keys[SDL_SCANCODE_D];
    bool r = keys[SDL_SCANCODE_R];
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

    Util::contain(&hero, groups_.getactive()->get_sprite_by_name("background"));

    camera.update(delta);

    groups_.getactive()->sort();

    //printf("%f,%f - %f,%f\n", hero.x, hero.y, background.x, background.y);
    //printf("%x, %x, %x\n", hero.texture->use(), monster.texture->use(), background.texture->use());
}

void Game::render()
{
    groups_.getactive()->draw(renderer);
    //ight.draw(renderer);
}

void Game::destroy()
{
    assets.destroy();
    for (auto &e : grass)
    {
        delete e;
    }
}
