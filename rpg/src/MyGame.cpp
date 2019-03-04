#include "MyGame.hpp"
#include "StaticGM.hpp"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

MyGame::MyGame() : engine::State()
{
    playerInput = true;
	playerMovement = true;
    todo = nullptr;
    todo_x = 0;
    todo_y = 0;
}

MyGame::~MyGame()
{

}

void MyGame::onEntry()
{
    transition.setAlpha(0);
    transition.fadeIn(200);
}

void MyGame::init(engine::Context& ctx)
{
	fs::path maps = fs::current_path() / "assets" / "maps";
	fs::path sprites = fs::current_path() / "assets" / "sprites";
    camera.setScreen(ctx.getWidth(), ctx.getHeight());

    //camera.setFocus(&hero);

    hero.init(ctx);
    hero.setSolid(true);
    hero.x = 10;
    hero.y = 10;

	room1.load((maps / "room1.json").generic_string());
	town1.load((maps / "town1.json").generic_string());
	room2.load((maps / "room2.json").generic_string());

	StaticGM::setFocus(&hero);
	StaticGM::addGroup("room1", &room1);
	StaticGM::addGroup("town1", &town1);
	StaticGM::addGroup("room2", &room2);
	StaticGM::setActive("town1");


    //dlg.push("this is a very very long string that will hopefully get divided up");
    //dlg.initFont(engine::Assets::getTexture("white-font.png"));
    tests();

    //hero_collisions = engine::Util::GetCollisions(&hero, gm.getActive());
    hero_collisions = engine::Util::GetCollisions(&hero, StaticGM::getActive());

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

    box.init(ctx, "fn");

	// need to optimize
	for (auto& e : town1.getNpcs())
	{
		e->setDialogueBox(box);
	}
	for (auto& e : room1.getNpcs())
	{
		e->setDialogueBox(box);
	}

	for (auto& e : room2.getNpcs())
	{
		e->setDialogueBox(box);
	}
}

void MyGame::tests()
{
    /*printf("starting tests...\n");

    Stats s;
    s.load(Config::getAssetPath() + "stats.json");
    s.write(Config::getAssetPath() + "stats.json");

    printf("done!\n");*/
}

void MyGame::update(float delta)
{
    updateKeys();

	op.setPointer((bool*)&kbd[SDL_SCANCODE_Z]);
	ol.setPointer((bool*)&kbd[SDL_SCANCODE_X]);
	playerInput = !transition.isRunning();
	playerMovement = !box.isVisible();

    hero.xvel = 0;
    hero.yvel = 0;

	if (!transition.isRunning() && todo != nullptr)
	{
		playerInput = false;
		todo->Enter();
		todo = nullptr;
        hero_collisions = engine::Util::getVelocityCollisions(
            &hero,
            StaticGM::getActive(),
            delta
        );
		hero.x = todo_x;
		hero.y = todo_y;
		transition.fadeIn(200);
	}

    if (playerInput) {
        bool up = kbd[SDL_SCANCODE_UP];
        bool down = kbd[SDL_SCANCODE_DOWN];
        bool left = kbd[SDL_SCANCODE_LEFT];
        bool right = kbd[SDL_SCANCODE_RIGHT];
        bool primary = kbd[SDL_SCANCODE_Z];
        bool secondary = kbd[SDL_SCANCODE_X];

		if (playerMovement)
		{
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
					StaticGM::getActive(),
					delta
				);
			}
		}

        if (op.altFire())
		{
			if (box.isVisible() && !playerMovement)
			{
				box.next();
			}
            else if (hero_collisions.size() > 0)
			{
				engine::Sprite* collider = hero_collisions[0];

				if (Door* d = dynamic_cast<Door*>(collider))
				{
					auto g = StaticGM::getGroup(d->getDest());
					std::vector<Door*> doors;
					g->getSpritesByType<Door>(doors);
					for (auto& e : doors)
					{
						if (e->getDest() == StaticGM::getActiveId())
						{
							todo_x = e->getExit().x;
							todo_y = e->getExit().y;
							break;
						}
					}
					transition.fadeOut(200);
					//d->Enter();
					todo = d;
				}
                else if (Npc* npc = dynamic_cast<Npc*>(collider))
				{
                    std::cout << "interacting with " << npc->getName() << std::endl;
                    npc->interact(&hero);
                }
            }
        }

        if (ol.altFire())
		{

        }

        auto collisions = engine::Util::getVelocityCollisions
		(
            &hero,
            StaticGM::getActive(),
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

    camera.x = hero.x + (hero.w / 2.0f) - (camera.getViewport().w / 2.0f);
    camera.y = hero.y + (hero.h / 2.0f) - (camera.getViewport().h / 2.0f);

	box.update(delta);

    transition.update();
    hero.update(delta);

    enemytest.update(delta);

    engine::Util::contain
	(
        &hero,
        StaticGM::getActive()->get_sprite_by_name("background")
    );

    camera.update();

	StaticGM::getActive()->sort();
}

void MyGame::render(engine::Context& ctx)
{
    StaticGM::getActive()->draw(camera, ctx);
    //dlg.render(&ctx);
	//dec.draw(&ctx);
	transition.draw(&ctx);
    enemytest.draw(ctx);
	//debug.draw(ctx);
    box.draw(ctx);
}

void MyGame::destroy()
{

}
