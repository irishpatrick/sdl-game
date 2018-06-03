#include "decision.hpp"
#include <SDL2/SDL.h>
#include "config.hpp"

namespace ui {

Decision::Decision() {
    visible = false;
    x = 0.0f;
    y = 0.0f;
    width = 100;
    height = 100;
}

Decision::~Decision() {

}

void Decision::update() {

}

void Decision::draw(engine::Context* c) {
    if (!visible) { return; }

    SDL_Rect fg;
    SDL_Rect bg;

    bg.x = x;
    bg.y = y;
    bg.w = width;
    bg.h = height;

    fg.x = x + 1;
    fg.y = y + 1;
    fg.w = width - 2;
    fg.h = height + 2;

    SDL_SetRenderDrawColor(c->getRenderer(), 0x00, 0x00, 0x00, 0xff);
    SDL_RenderFillRect(c->getRenderer(), &bg);

    SDL_SetRenderDrawColor(c->getRenderer(), 0xff, 0xff, 0xff, 0xff);
    SDL_RenderFillRect(c->getRenderer(), &fg);

	if (selected == YES) {
		Config::getFont()->setColor(Config::getActiveColor());
		Config::getFont()->renderString("yes", x + PADDING, y + PADDING, c->getRenderer());
		Config::getFont()->setColor(Config::getDefaultColor());
		Config::getFont()->renderString("no", x + PADDING, y + (height / 2) + PADDING, c->getRenderer());
	}
	else if (selected == NO) {
		Config::getFont()->setColor(Config::getDefaultColor());
		Config::getFont()->renderString("yes", x + PADDING, y + PADDING, c->getRenderer());
		Config::getFont()->setColor(Config::getActiveColor());
		Config::getFont()->renderString("no", x + PADDING, y + (height / 2) + PADDING, c->getRenderer());
	}
	
}

}
