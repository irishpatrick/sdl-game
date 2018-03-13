#include "background.h"

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

Background::Background() {
    for (int i=0; i<3; i++) {
        engine::Sprite* n = new engine::Sprite();
        n->setTexture(engine::Assets::getTexture("background.png"));
        n->x = (512 * i) - 512;
        n->y = 0;
        frames.push_back(n);
    }

    speed = 400.0f;
}

Background::~Background() {
    for (int i=0; i<3; i++) {
        delete frames[i];
    }
}

void Background::setSpeed(float s) {
    speed = s;
}

void Background::update(float delta) {
    for (int i=0; i<3; i++) {
        if (frames[i]->x < -512) {
            int n = mod(i - 1, 3);
            frames[i]->x = frames[n]->x + frames[n]->w;
        }
        frames[i]->x -= speed * delta;
    }
}

void Background::draw(SDL_Renderer* r)
{
    for (int i=0; i<3; i++) {
        frames[i]->draw(r);
    }
}
