#include "Game.hpp"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

Game::Game() : State()
{
    playerInput = true;
    todo = nullptr;
    todo_x = 0;
    todo_y = 0;
}

Game::~Game()
{

}

void Game::init(engine::Context& ctx)
{
	fs::path maps = fs::current_path() / "assets" / "maps";
	fs::path sprites = fs::current_path() / "assets" / "sprites";
    camera.setScreen(ctx.getWidth(), ctx.getHeight());

    camera.setFocus(&hero);

    hero.init(ctx);
    hero.setSolid(true);
    hero.x = 10;
    hero.y = 10;

    //gm.setcamera(&camera);
    gm.setFocus(&hero);
    gm.loadGroup("room1", (maps / "room1.json").generic_string());
    gm.loadGroup("town1", (maps / "town1.json").generic_string());
    std::cout << "loading room2.json" << std::endl;
    gm.loadGroup("room2", (maps / "room2.json").generic_string());
    //gm.addgroup("stage", &stage);
    gm.setActive("town1");

    //dlg.push("this is a very very long string that will hopefully get divided up");
    //dlg.initFont(engine::Assets::getTexture("white-font.png"));
    tests();

    hero_collisions = engine::Util::GetCollisions(&hero, gm.getActive());

    /*ui::Config::initFont(engine::Assets::getTexture("white-font.png"), 0.055f);
    ui::Config::setActiveColor(255, 255, 0);
    ui::Config::setDefaultColor(0, 0, 0);
    dec.setSelection(ui::Decision::NO);
    dec.setVisible(false);
    dec.x = 100;
    dec.y = 100;

    dlg.setWidth(300, 80);
    //dlg.push("this is a very very long string that will hopefully get divided up");
	*/

    //enemytest.InitAnimation((sprites / fs::path("monster1.json")).generic_string());
    //enemytest.getAnimation()->Start("all", true);

	debug.init((fs::current_path() / "assets" / "font.ttf").generic_string(), ctx);
	debug.addLine("hello debug");
	debug.addLine("new line");

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
            gm.getActive(),
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

		if (dec.isVisible()) 
		{
			if (up)
			{
				dec.setSelection(ui::Decision::YES);
			}
			if (down)
			{
				dec.setSelection(ui::Decision::NO);
			}
			if (op.fire())
			{
				dec.setVisible(false);
			}
		}
		else if (dlg.isVisible())
		{
            std::cout << "dialogue is visible" << std::endl;
		}
		else {
			if ((up || down) && (left || right))
			{
				float v = sqrt(pow(hero.getMaxSpeed(), 2) / 2.0);
				hero.speed = v;
			}
			else
			{
				hero.speed = hero.getMaxSpeed();
			}

			if (up)
			{
				hero.yvel = -hero.speed;
			}
			if (down)
			{
				hero.yvel = hero.speed;
			}
			if (left) {
				hero.xvel = -hero.speed;
			}
			if (right)
			{
				hero.xvel = hero.speed;
			}

			if (up || down || left || right)
			{
				hero_collisions = engine::Util::getVelocityCollisions(
					&hero,
					gm.getActive(),
					delta
				);
			}
		}

        /*if (!dlg.isVisible()) {

        }*/

        if (op.fire())
		{
            if (dlg.isVisible())
			{
                dlg.pop();
            }
            else if (hero_collisions.size() > 0) {
                engine::Sprite* collider = hero_collisions[0];

				if (Door* d = dynamic_cast<Door*>(collider))
				{
					auto g = gm.getGroup(d->getDest());
					std::vector<Door*> doors;
					g->getSpritesByType<Door>(doors);
					for (auto& e : doors)
					{
						if (e->getDest() == gm.getActiveId())
						{
							todo_x = e->getExit().x;
							todo_y = e->getExit().y;
							break;
						}
					}
					transition.fadeOut(250);
					//d->Enter();
					todo = d;
				}
                else if (Npc* npc = dynamic_cast<Npc*>(collider))
				{
                    std::cout << "interacting with " << npc->getName() << std::endl;
                    npc->interact(&hero, &dlg);
                }
            }
        }

        if (ol.fire()) 
		{

        }

        auto collisions = engine::Util::getVelocityCollisions
		(
            &hero,
            gm.getActive(),
            delta
        );

        if (collisions.size() > 0)
		{
            for (auto& e : collisions)
			{
                std::string result = engine::Util::checkVelocityCollision(
                    &hero,
                    e,
                    delta
                );
				//engine::BoundingBox& rebox = e->getRelativeBoundingBox();
				engine::BoundingBox& rhbox = hero.getRelativeBoundingBox();
				engine::BoundingBox& ebox = e->getBoundingBox();
				engine::BoundingBox& hbox = hero.getBoundingBox();


                if (result == "north")
				{
                    hero.yvel = 0;
                    //hero.y = ebox.y + hbox.h;
					hero.y = ebox.y + ebox.h - rhbox.y;
                }
                else if (result == "south")
				{
                    hero.yvel = 0;
					hero.y = ebox.y - (rhbox.y + hbox.h);
					//hero.y = ebox.y - hero.h + hbox.y - hbox.h;
					//hero.y = ebox.y +
				}
                else if (result == "east")
				{
                    hero.xvel = 0;
                    hero.x = ebox.x - (rhbox.x + hbox.w);
                }
                else if (result == "west")
				{
                    hero.xvel = 0;
                    hero.x = ebox.x + ebox.w - rhbox.x;
                }
                else
				{
                    std::cout << "collision detection problem" << std::endl;
                }
            }
        }
    }

    transition.update();
    hero.update(delta);

    enemytest.update(delta);

    engine::Util::contain
	(
        &hero,
        gm.getActive()->get_sprite_by_name("background")
    );

    camera.update(delta);

    gm.getActive()->sort();
}

void Game::render(engine::Context& ctx)
{
    gm.getActive()->draw(camera, ctx);
    dlg.render(&ctx);
	dec.draw(&ctx);
	transition.draw(&ctx);
    enemytest.draw(ctx);
	debug.draw(ctx);
}

void Game::destroy()
{

}
