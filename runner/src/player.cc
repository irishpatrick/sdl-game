#include "player.h"

Player::Player(): Sprite() {
    setTexture(Assets::getTexture("player.png"));
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

    cout << "velocity: " << velocity << " Ft: " << Ft << " Fa: " << Fa << endl;
}

/*void Player::update(float delta) {

    cout << "jumping: " << jumping << " change: " << change << " time: " << t << " velocity: " << velocity << endl;

    if (last == !jumping) {
        change = true;
        //t = 0;
    } else {
        change = false;
    }

    if (jumping)
    {
        Ft += 10 * delta;
    } else {
        Ft = 0;
    }

    if (change) {
        vi = velocity;
    }

    float Fsum = Ft - Fg + Fn;
    float a = Fsum / mass;
    velocity = vi + (a * t);

    t += delta;

    if (y > ground - h) {
        y = ground - h;
        velocity = 0;
        t = 0;
    }

    y -= velocity;

    if (jumping) {
        velocity = -grav.solve(t);
        t += delta;
    } else {
        velocity = grav.solve(t);
        t -= delta;
    }
    if (jumping && t < path.d) {
        printf("%f: %f\n", t, path.solve(t));
        y = ground - h + path.solve(t);
        t += delta;
        if (t > path.d) {
            t = 0;
            y = ground - h;
            jumping = false;
        }
    }

    y += velocity;

    if (y > ground - h) {
        y = ground - h;
        velocity = 0;
        t = 0;
    }

    cout << " velocity: " << velocity << " y: " << y << endl;

    last = jumping;
    jumping = false;
}*/
