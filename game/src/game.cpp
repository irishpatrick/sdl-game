#include "game.hpp"

Game::Game(): engine::State() {
    playerInput = true;
    todo = nullptr;
    todo_x = 0;
    todo_y = 0;
}

Game::~Game() {

}

void Game::init(engine::Context& ctx) {
    std::string maps = Config::getAssetPath() + "maps/";
    std::string sprites = Config::getAssetPath() + "sprites/";
    camera.screen(ctx.getWidth(), ctx.getHeight());

    camera.setFocus(&hero);

	hero.init(ctx);
    hero.pos(10,10);

    groups_.setcamera(&camera);
    groups_.setfocus(&hero);
    groups_.loadgroup("room1", maps + "room1.json");
    groups_.loadgroup("town1", maps + "town1.json");
    std::cout << "loading room2.json" << std::endl;
    groups_.loadgroup("room2", maps + "room2.json");
    //groups_.addgroup("stage", &stage);
    groups_.setactive("town1");
    printf("done!\n");

    //test.InitFromJson(root + "animtest.json");
    animtest.InitAnimation(sprites + "animtest.json");
    animtest.GetAnimation()->Start("all", true);
    stage.add(&animtest);

    dlg.setWidth(300, 80);
	//dlg.push("this is a very very long string that will hopefully get divided up");
    dlg.initFont(engine::Assets::getTexture("white-font.png"));
    tests();

    hero_collisions = engine::Util::GetCollisions(&hero, groups_.getactive());

	ui::Config::initFont(engine::Assets::getTexture("white-font.png"), 0.055f);
	ui::Config::setActiveColor(255, 255, 0);
	ui::Config::setDefaultColor(0, 0, 0);
	dec.setSelection(ui::Decision::NO);
	dec.setVisible(false);
	dec.x = 100;
	dec.y = 100;
}

void Game::tests() {
    /*printf("starting tests...\n");

    Stats s;
    s.load(Config::getAssetPath() + "stats.json");
    s.write(Config::getAssetPath() + "stats.json");

    printf("done!\n");*/
}

void Game::update(float delta, const uint8_t* keys) {

    playerInput = !transition.isRunning();

    hero.xvel = 0;
    hero.yvel = 0;

	if (!transition.isRunning() && todo != nullptr) {
		playerInput = false;
		todo->Enter();
		todo = nullptr;
        hero_collisions = engine::Util::getVelocityCollisions(
            &hero,
            groups_.getactive(),
            delta
        );
		hero.x = todo_x;
		hero.y = todo_y;
		transition.fadeIn(250);
	}

    if (playerInput) {
        bool up = keys[SDL_SCANCODE_UP];
        bool down = keys[SDL_SCANCODE_DOWN];
        bool left = keys[SDL_SCANCODE_LEFT];
        bool right = keys[SDL_SCANCODE_RIGHT];
        bool primary = keys[SDL_SCANCODE_Z];
        bool secondary = keys[SDL_SCANCODE_X];
		op.check(primary);
		ol.check(secondary);

		if (dec.isVisible()) {
			if (up) {
				dec.setSelection(ui::Decision::YES);
			}
			if (down) {
				dec.setSelection(ui::Decision::NO);
			}
			if (op.fire()) {
				dec.setVisible(false);
			}
		}
		else if (dlg.isVisible()) {

		}
		else {
			if ((up || down) && (left || right)) {
				float v = sqrt(pow(hero.getMaxSpeed(), 2) / 2.0);
				hero.speed = v;
			}
			else {
				hero.speed = hero.getMaxSpeed();
			}

			if (up) {
				hero.yvel = -hero.speed;
			}
			if (down) {
				hero.yvel = hero.speed;
			}
			if (left) {
				hero.xvel = -hero.speed;
			}
			if (right) {
				hero.xvel = hero.speed;
			}

			if (up || down || left || right) {
				hero_collisions = engine::Util::getVelocityCollisions(
					&hero,
					groups_.getactive(),
					delta
				);
			}
		}

        if (!dlg.isVisible()) {

        }

        if (op.fire()) {
            if (dlg.isVisible()) {
                dlg.pop();
            }
            else if (hero_collisions.size() > 0) {
                engine::Sprite* collider = hero_collisions[0];

                if (Door* d = dynamic_cast<Door*>(collider)) {
                    auto g = groups_.getGroup(d->getDest());
                    std::vector<Door*> doors;
                    g->getSpritesByType<Door>(doors);
                    for (auto& e : doors) {
                        if (e->getDest() == groups_.getActiveId()) {
                            todo_x = e->getExit().x;
                            todo_y = e->getExit().y;
                            break;
                        }
                    }
                    transition.fadeOut(250);
                    //d->Enter();
                    todo = d;
                }
                else if (Npc* npc = dynamic_cast<Npc*>(collider)) {
                    std::cout << "interacting with " << npc->getName() << std::endl;
                    npc->interact(&hero, &dlg);
                }
            }
        }

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
    }

    transition.update();
    hero.velocityUpdate(delta);

    animtest.update(delta);

    engine::Util::contain(
        &hero,
        groups_.getactive()->get_sprite_by_name("background")
    );

    camera.update(delta);

    groups_.getactive()->sort();
}

void Game::render(engine::Context& ctx) {
    groups_.getactive()->draw(ctx.getRenderer());
    dlg.render(&ctx);
	dec.draw(&ctx);
	transition.draw(&ctx);
}

void Game::destroy() {

}
