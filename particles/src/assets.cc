#include "assets.h"

namespace particles {

static map<string, SDL_Texture*> texmap;
static SDL_Renderer* renderer;

vector<string> split(const string& s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while(getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

void Assets::registerAll(sol::state& lua) {
    lua["loadTexture"] = Assets::loadTexture;
}

int Assets::loadTexture(const string& fn) {
    if (renderer == nullptr) {
        return -1;
    }
    SDL_Texture* t = IMG_LoadTexture(renderer, fn.c_str());
    cout << "fn: " << fn << endl;
    if (t == nullptr) {
        return -1;
    }

    auto keys = split(fn, '/');
    string key = keys[keys.size()-1];

    texmap[key] = t;

    return 0;
}

SDL_Texture* Assets::getTexture(const string& key) {
    if (texmap.find(key) != texmap.end()) {
        return texmap[key];
    } else {
        return nullptr;
    }
}

void Assets::setRenderer(SDL_Renderer* r) {
    renderer = r;
}

}
