#include "game.hpp"

Game::Game(engine::Context* c): engine::State(c) {

}

Game::~Game() {

}

void Game::init() {
    std::string maps = Config::getAssetPath() + "maps/";
    std::string sprites = Config::getAssetPath() + "sprites/";
    camera.screen(ctx->getWidth(), ctx->getHeight());

    camera.setFocus(&hero);

    hero.setTexture(engine::Assets::getTexture("hero.png"));
    hero.setMaxSpeed(250.0f);
    hero.name = "hero";

    hero.queryTexture();

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

    dlg.setWidth(300, 80);
	dlg.push("this is a very very long string that will hopefully get divided up");
    dlg.initFont(engine::Assets::getTexture("out.png"));

    tests();

    hero_collisions = engine::Util::GetCollisions(&hero, groups_.getactive());
}

void Game::tests() {
    printf("starting tests...\n");

    Stats s;
    s.load(Config::getAssetPath() + "stats.json");
    s.write(Config::getAssetPath() + "stats.json");

    printf("done!\n");
}

void Game::update(float delta, const uint8_t* keys) {
    bool w = keys[SDL_SCANCODE_W];
    bool s = keys[SDL_SCANCODE_S];
    bool a = keys[SDL_SCANCODE_A];
    bool d = keys[SDL_SCANCODE_D];
    bool p = keys[SDL_SCANCODE_P];
    bool l = keys[SDL_SCANCODE_L];

    //cout << engine::Mouse::left << endl;
    //cout << engine::Mouse::x << ", " << engine::Mouse::y << endl;

    if (engine::Mouse::left) {
        cout << "click: " << engine::Mouse::x << ", " << engine::Mouse::y << endl;
    }

    hero.xvel = 0;
    hero.yvel = 0;

    if (!dlg.isVisible()) {
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
    }

    op.check(p);
    if (op.fire()) {
        if (dlg.isVisible()) {
            dlg.pop();
        }
        else if (hero_collisions.size() > 0) {
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
            else if (Npc* npc = dynamic_cast<Npc*>(collider)) {
                std::cout << "interacting with " << npc->getName() << std::endl;
                npc->interact(&hero, &dlg);
            }
        }
    }

    ol.check(l);
    if (ol.fire()) {

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
    dlg.render(ctx);
}

void Game::destroy() {
    engine::Assets::destroy();
}
