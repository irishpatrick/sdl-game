#include "game.h"

Game::Game(engine::Context* c): engine::State(c) {

}

Game::~Game() {

}

void Game::init() {
    printf("loading assets\n");

    string textures = Config::assetpath() + "textures/";
    string maps = Config::assetpath() + "maps/";
    string root = Config::assetpath();
    string sprites = Config::assetpath() + "sprites/";

    SDL_Renderer* r = ctx->getRenderer();

    engine::Assets::loadTexture(textures + "med-background.png", r);
    engine::Assets::loadTexture(textures + "hero.png", r);
    engine::Assets::loadTexture(textures + "monster.png", r);
    engine::Assets::loadTexture(textures + "grass1.png", r);
    engine::Assets::loadTexture(textures + "room-bg.png", r);
    engine::Assets::loadTexture(textures + "opposite.png", r);
    engine::Assets::loadTexture(textures + "animtest.png", r);
    engine::Assets::loadTexture(textures + "door.png", r);
    camera.screen(ctx->getWidth(), ctx->getHeight());

    camera.setFocus(&hero);

    hero.setTexture(engine::Assets::getTexture("hero.png"));
    hero.setMaxSpeed(250.0f);
    hero.name = "hero";

    /*monster.setTexture(engine::Assets::getTexture("monster.png"));
    monster.pos(150, 150);
    monster.name = "monster";

    background.setTexture(engine::Assets::getTexture("med-background.png"));
    background.name = "background";
    background.solid = false;

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

    stage.setCamera(&camera);*/

    engine::Assets::getFutures();

    //light.querytexture();
    hero.queryTexture();
    //monster.queryTexture();
    //background.queryTexture();
    //doortest.queryTexture();

    //hero.pos((w / 2) - (hero.w / 2), (h / 2) - (hero.h / 2));
    hero.pos(10,10);

    groups_.setcamera(&camera);
    groups_.setfocus(&hero);
    groups_.loadgroup("room", maps + "testroom.json");
    groups_.loadgroup("town1", maps + "town1.json");
    //groups_.addgroup("stage", &stage);
    groups_.setactive("town1");
    printf("done!\n");

    //test.InitFromJson(root + "animtest.json");
    animtest.InitAnimation(sprites + "animtest.json");
    animtest.GetAnimation()->Start("all", true);
    stage.add(&animtest);

    tests();

    hero_collisions = engine::Util::GetCollisions(&hero, groups_.getactive());
}

void Game::tests() {
    printf("starting tests...\n");

    Stats s;
    s.load(Config::assetpath() + "stats.json");

    /*list.x = 100;
    list.y = 100;
    list.setFont(renderer, "../../games/rpg/assets/fonts/font");
    list.addItem("hi");
    list.addItem("world");
    list.addItem("very long item in list");
    list.setVisible(true);*/

    printf("done!\n");
}

void Game::update(float delta, const uint8_t* keys) {
    bool w = keys[SDL_SCANCODE_W];
    bool s = keys[SDL_SCANCODE_S];
    bool a = keys[SDL_SCANCODE_A];
    bool d = keys[SDL_SCANCODE_D];
    bool p = keys[SDL_SCANCODE_P];

    /*if ((w || s) && (a || d)) {
        hero_collisions = engine::Util::GetCollisions(&hero, groups_.getactive());
        float v = sqrt(pow(hero.getMaxSpeed(), 2) / 2.0);
        hero.speed = v;
    } else {
        hero.speed = hero.getMaxSpeed();
    }

    if (w) {
        hero.y -= hero.speed * delta;
    }
    if (s) {
        hero.y += hero.speed * delta;
    }
    if (a) {
        hero.x -= hero.speed * delta;
    }
    if (d) {
        hero.x += hero.speed * delta;
    }

    if ((w || s) || (a || d)) {
        hero_collisions = engine::Util::GetCollisions(&hero, groups_.getactive());
    }

    //hero_collisions = Util::GetCollisions(&hero, groups_.getactive());

    op.check(p);
    if (op.fire()) {
        if (hero_collisions.size() > 0) {
            engine::Sprite* collider = hero_collisions[0];
            if (Door* d = dynamic_cast<Door*>(collider)) {
                // success
                //printf("entering door!\n");
                //hero.pos(d->GetExit()->x, d->GetExit()->y);
                //d->SetExit(hero.x, hero.y);
                if (!hero.getDoorStack()->isEmpty()) {
                    //printf("stack not empty!\n");
                    engine::Point pos = hero.getDoorStack()->pop();
                    hero.x = pos.x;
                    hero.y = pos.y;
                }
                else {
                    hero.getDoorStack()->push(*d->GetExit());
                }
                //hero.ResetCollision();

                d->Enter();
            }
        }
    }

    for (auto& e: groups_.getactive()->getSprites()) {
        if (hero.getUUID() == e->getUUID()) {
            continue;
        }
        if (background.getUUID() == e->getUUID()) {
            continue;
        }

        const string result = engine::Util::checkCollision(&hero, e);
        if (result == "north") {
            hero.y += hero.speed * delta;
        }
        if (result == "south") {
            hero.y -= hero.speed * delta;
        }
        if (result == "east") {
            hero.x -= hero.speed * delta;
        }
        if (result == "west") {
            hero.x += hero.speed * delta;
        }
    }*/

    // lag
    //SDL_Delay(70);

    hero.xvel = 0;
    hero.yvel = 0;

    if ((w || s) && (a || d)) {
        hero_collisions = engine::Util::getVelocityCollisions(
            &hero,
            groups_.getactive(),
            delta
        );
        //cout << hero_collisions.size() << endl;
        float v = sqrt(pow(hero.getMaxSpeed(), 2) / 2.0);
        hero.speed = v;
    } else {
        hero.speed = hero.getMaxSpeed();
    }

    if (w) {
        hero.yvel = -hero.speed;
    }
    if (s) {
        hero.yvel = hero.speed;
    }
    if (a) {
        hero.xvel = -hero.speed;
    }
    if (d) {
        hero.xvel = hero.speed;
    }

    if (w || s || a || d) {
        hero_collisions = engine::Util::getVelocityCollisions(
            &hero,
            groups_.getactive(),
            delta
        );
    }

    op.check(p);
    if (op.fire()) {
        if (hero_collisions.size() > 0) {
            engine::Sprite* collider = hero_collisions[0];
            if (Door* d = dynamic_cast<Door*>(collider)) {
                // success
                //printf("entering door!\n");
                //hero.pos(d->GetExit()->x, d->GetExit()->y);
                //d->SetExit(hero.x, hero.y);
                if (!hero.getDoorStack()->isEmpty()) {
                    //printf("stack not empty!\n");
                    engine::Point pos = hero.getDoorStack()->pop();
                    hero.x = pos.x;
                    hero.y = pos.y;
                }
                else {
                    hero.getDoorStack()->push(*d->GetExit());
                }
                //hero.ResetCollision();

                d->Enter();
            }
        }
    }

    auto collisions = engine::Util::getVelocityCollisions(
        &hero,
        groups_.getactive(),
        delta
    );

    if (collisions.size() > 0) {
        for (auto& e : collisions) {
            string result = engine::Util::checkVelocityCollision(
                &hero,
                e,
                delta
            );
            SDL_Rect ebox = engine::Util::getAABB(e, 16);
            SDL_Rect hbox = engine::Util::getAABB(&hero, 16);
            if (result == "north") {
                hero.yvel = 0;
                hero.y = ebox.y + ebox.h - hbox.h;
            }
            else if (result == "south") {
                hero.yvel = 0;
                hero.y = ebox.y - hero.h;
            }
            else if (result == "east") {
                hero.xvel = 0;
                hero.x = ebox.x - hero.w;
            }
            else if (result == "west") {
                hero.xvel = 0;
                hero.x = ebox.x + ebox.w;
            }
            else {
                cout << "collision detection problem" << endl;
            }
        }
    }

    hero.velocityUpdate(delta);

    animtest.update(delta);

    engine::Util::contain(
        &hero,
        groups_.getactive()->get_sprite_by_name("background")
    );

    camera.update(delta);

    groups_.getactive()->sort();
}

void Game::render() {
    groups_.getactive()->draw(ctx->getRenderer());
    //list.draw(renderer);
}

void Game::destroy() {
    engine::Assets::destroy();
    for (auto &e : grass) {
        delete e;
    }
}
