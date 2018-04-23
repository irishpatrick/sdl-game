#include "floor.h"

bool inside(int x, int y, Room* a) {
    return (
        x <= a->x + a->h &&
        x >= a->x &&
        y <= a->x + a->h &&
        y >= a->y
    );
}

bool intersects(Room* a, Room* b) {
    return (
        a->x < b->x + b->h &&
        a->x + a->h > b->x &&
        a->y < b->x + b->h &&
        a->y + a->h > b->y
    );
}

int random(int min, int max) {
    //cout << "random(" << min << ", " << max << ")" << endl;
    return (rand() % (max - min)) + min;
}

Floor::Floor(): GridSprite() {
    nrooms = 0;
    world = 0;
}

Floor::~Floor() {
    free(rooms);
}

void Floor::generate(int numrooms) {
    srand(time(nullptr));
    nrooms = numrooms;
    rooms = (Room*)malloc(nrooms * sizeof(Room));
    int padding = 4;
    world = 64;

    // generate rooms
    for (int i=0; i<nrooms; i++) {
        rooms[i].w = random(2,8);
        rooms[i].h = random(2,8);
    }

    // place first room
    rooms[0].x = random(0,world);
    rooms[0].y = random(0,world);

    // place remaining rooms
    for (int i=1; i<nrooms; i++) {
        Room* last = &rooms[i-1];
        Room* current = &rooms[i];

        int xmin = last->x - current->w - padding;
        int xmax = last->x + last->w + padding;
        int ymin = last->y - current->h - padding;
        int ymax = last->y + last->h + padding;

        if (xmin <= 0 || ymin <= 0) {
            cout << "bad placement! moving on..." << endl;
            continue;
        }

        int xopts[] = {random(0,xmin), random(xmax,world)};
        int yopts[] = {random(0,ymin), random(ymax,world)};

        current->x = xopts[random(0,1)];
        current->y = yopts[random(0,1)];
        //current->x = random(0,64);
        //current->y = random(0,64);
    }

    cout << "final positions:" << endl;
    for (int i=0; i<nrooms; i++) {
        Room* c = &rooms[i];
        cout << i << ": " << c->x << "," << c->y << "," << c->w << "," << c->h << endl;
    }
}

void Floor::printMap() {
    char grid[world][world];

    for (int r=0; r<world; r++) {
        for (int c=0; c<world; c++) {
            grid[r][c] = '.';
        }
    }

    for (int i=0; i<nrooms; i++) {
        cout << "room #" << i << endl;
        for (int r=0; r<world; r++) {
            for (int c=0; c<world; c++) {
                if (inside(c,r,&rooms[i])) {
                    grid[c][r] = 'R';
                }
            }
        }
    }

    for (int y=0; y<world; y++) {
        for (int x=0; x<world; x++) {
            cout << grid[y][x] << " ";
        }
        cout << endl;
    }
}

void Floor::velocityUpdate(float delta) {

}

void Floor::draw(SDL_Renderer* r) {

}
