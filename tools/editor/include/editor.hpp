#pragma once

#include <cstdint>
#include <engine.hpp>

class Editor : public engine::State {
public:
	Editor();
	~Editor();

	void init(engine::Context&) override;
	void update(float, const uint8_t*) override;
	void render(engine::Context&) override;

};