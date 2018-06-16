#pragma once

#include <engine.hpp>
#include <vector>

class Game: public engine::State {

public:
	Game();
	~Game();

	void init(engine::Context&);
	void update(float, const uint8_t*);
	void render(engine::Context&);

	void destroy();

private:
	
};