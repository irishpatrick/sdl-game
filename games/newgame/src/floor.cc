#include "floor.h"
#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
#include <engine.h>

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

void Floor::generate(int n) {
    srand(time(nullptr));

    nrooms = n;
    rooms = (Room*)malloc(nrooms * sizeof(Room));

    // randomly generate rooms
    for (int i=0;i<nrooms;i++) {
        Room* c = &rooms[i];
        c->w = random(3,6);
        c->h = random(3,6);
    }

    // randomly place rooms
    int padding = 1;
    int dist = 8;
    int last_side = -1;
    rooms[0].x = 0;
    rooms[0].y = 0;
    for (int i=1;i<nrooms;i++) {
        Room* l = &rooms[i-1];
        Room* c = &rooms[i];
        int side = random(0,3);
        if (last_side == side) {
            side = (side + 1) % 3;
        }
        switch (side) {
            case 0:
            // north
            c->x = l->x; // temporary
            c->y = random(l->y - padding, l->y - dist);
            last_side = 0;
            break;

            case 1:
            // east
            last_side = 1;
            break;

            case 2:
            // south
            c->x = l->x;
            c->y = random(l->y + l->h + padding, l->y + l->h + dist);
            last_side = 2;
            break;

            case 3:
            // west
            last_side = 3;
            break;
        }
    }

    // connect rooms
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
