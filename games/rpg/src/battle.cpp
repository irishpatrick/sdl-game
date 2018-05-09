#include "battle.hpp"

Battle::Battle(engine::Context* c): engine::State(c) {

}

Battle::~Battle() {

}

void Battle::init() {
    dialogue.setWidth(300, 80);
    dialogue.initFont(engine::Assets::getTexture("out.png"));

    bg.setTexture(engine::Assets::getTexture("battle-bg.png"));
    bg.queryTexture();
    bg.x = 0;
    bg.y = 0;
}

void Battle::addCombatants(std::vector<engine::Sprite*>& a, std::vector<engine::Sprite*>& e) {
    for (auto& sprite : a) {

    }

    for (auto& sprite : e) {

    }
}

void Battle::update(float delta, const uint8_t* keys) {


    bg.velocityUpdate(delta);
}

void Battle::render() {
    bg.draw(ctx->getRenderer());
}

void Battle::destroy() {

}
