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
    int n;

    n = 0;
    std::string name;
    for (auto& sprite : a) {
        name = "battle-" + sprite->getTexture()->getName();
        allies[n++].setTexture(engine::Assets::getTexture(name));
    }

    n = 0;
    for (auto& sprite : e) {
        name = "battle-" + sprite->getTexture()->getName();
        enemies[n++].setTexture(engine::Assets::getTexture(name));
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
