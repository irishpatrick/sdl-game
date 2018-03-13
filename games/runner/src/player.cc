#include "player.h"

Player::Player(): engine::Sprite() {
    setTexture(engine::Assets::getTexture("player.png"));
    ground = 0;
    fall = 0;
    jumping = false;
    velocity = 0;
    t = 0;

    Fg = 30;
    Ft = 0;
    Fn = 0;
    Fa = 0;
    mass = 5;
    vi = 0;

    jet.script("../../games/runner/assets/jet.lua");
}

Player::~Player() {

}

void Player::setGround(float g) {
    ground = g;
}

void Player::jump(float j) {
    jumping = true;
}

void Player::update(float delta) {
    if (jumping) {
        Ft = 300;
    } else {
        Ft = 0;
    }

    float k;
    if (velocity != 0) {
        k = (velocity / fabs(velocity)) * 1.2;
    } else {
        k = 0;
    }

    Fa = k * (velocity * velocity);

    float Fsum = Ft - (Fg * mass) - Fa;
    float a = Fsum / mass;

    velocity += a * delta;

    y -= velocity;

    if (y > ground - h) {
        y = ground - h;
        velocity = 0;
    }

    if (y < 0) {
        y = 0;
        velocity = 0;
    }

    jumping = false;

    jet.x = x;
    jet.y = y;
    jet.update(delta);

    //cout << "velocity: " << velocity << " Ft: " << Ft << " Fa: " << Fa << endl;
}

void Player::draw(SDL_Renderer* r) {
    Sprite::draw(r);
    jet.draw(r);
}
