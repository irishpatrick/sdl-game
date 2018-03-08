#include "player.h"

Player::Player(): Sprite() {
    setTexture(Assets::getTexture("player.png"));
    ground = 0;
    fall = 0;
    jumping = false;
    velocity = 0;
    t = 0;
    path = Quadratic(300,1);
    grav = Sigmoid(10,5,1);
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

    cout << "jumping: " << jumping << " change: " << change << " time: " << t << endl;

    if (last == !jumping) {
        change = true;
        t = 0;
    } else {
        change = false;
    }

    if (jumping) {
        velocity = -1 * grav.solve(t);
    } else {
        velocity = grav.solve(t);
    }

    t += delta;
    /*if (jumping && t < path.d) {
        printf("%f: %f\n", t, path.solve(t));
        y = ground - h + path.solve(t);
        t += delta;
        if (t > path.d) {
            t = 0;
            y = ground - h;
            jumping = false;
        }
    }*/

    /*if (y > ground - h) {
        y = ground - h;
        t = 0;
        fall = 0;
        jumping = true;
    }*/

    y += velocity;

    last = jumping;
    jumping = false;
}
