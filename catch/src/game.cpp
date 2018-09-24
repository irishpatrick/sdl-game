#include "game.hpp"

Game::Game(): engine::State() {
	num_berries = 6;
	score = 0;
}

Game::~Game() {

}

void Game::init(engine::Context& ctx) {
	spoon.init();
	spoon.x = 0;
	spoon.y = ctx.getHeight() - spoon.h - 20;

	for (int i = 0; i < num_berries; i++) {
		Raspberry* r = new Raspberry();
		r->init(ctx);
		berries.push_back(r);
	}
}

void Game::update(float delta, const uint8_t* keys) {
	bool left = keys[SDL_SCANCODE_LEFT];
	bool right = keys[SDL_SCANCODE_RIGHT];

	if (left && right) {}
	else if (left) {
		spoon.xvel = -350;
	}
	else if (right) {
		spoon.xvel = 350;
	}
	else {
		spoon.xvel = 0;
	}

	std::vector<engine::Sprite*> berry_sprites;
	for (auto& e : berries) {
		berry_sprites.push_back((engine::Sprite*)e);
	}
	std::vector<engine::Sprite*> catches = engine::Util::getVelocityCollisions(&spoon, berry_sprites, delta);

	for (auto& e : catches) {
		//std::cout << "catch!" << std::endl;
		if (Raspberry* r = dynamic_cast<Raspberry*>(e)) {
			//std::cout << "successful cast" << std::endl;
			r->reset();
		}
	}

	for (auto& e : berries) {
		e->SetVisible(true);
		e->update(delta);
	}
	spoon.update(delta);
}

void Game::render(engine::Context& ctx) {
	spoon.draw(ctx);

	for (auto& e : berries) {
		e->draw(ctx);
	}
}

void Game::destroy() {
	for (auto& e : berries) {
		delete e;
	}
}