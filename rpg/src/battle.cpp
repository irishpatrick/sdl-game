#include "battle.hpp"

Battle::Battle(): engine::State() {

}

Battle::~Battle() {

}

void Battle::init(engine::Context& ctx) {
    dialogue.setWidth(300, 80);
    dialogue.initFont(engine::Assets::getTexture("out.png"));

    bg.setTexture(engine::Assets::getTexture("battle-bg.png"));
    bg.queryTexture();
    bg.x = 0;
    bg.y = 0;
}

void Battle::setBackground(const std::string& bg) {

}

void Battle::addCombatants(std::vector<engine::Sprite*>& a, std::vector<engine::Sprite*>& e) {
    // get the battle versions of each sprite

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

void Battle::render(engine::Context& ctx) {
    for (auto& e : enemies) {
        e.draw(ctx);
    }
    bg.draw(ctx.getRenderer());
}

void Battle::destroy() {

}
