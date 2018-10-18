#pragma once

#include <engine.hpp>
#include "Spoon.hpp"
#include "Raspberry.hpp"
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
	std::vector<Raspberry*> berries;
	Spoon spoon;
	int num_berries;
	int score;
};
