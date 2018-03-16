#include "assets.h"

namespace particles {

static map<string, SDL_Texture*> texmap;
static SDL_Renderer* renderer = nullptr;

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

string Assets::loadTexture(const string& fn) {
    if (renderer == nullptr) {
        return "bad renderer";
    }
    SDL_Texture* t = IMG_LoadTexture(renderer, fn.c_str());
    if (t == nullptr) {
        ostringstream os;
        os << IMG_GetError();
        return os.str();
    }

    auto keys = split(fn, '/');
    string key = keys[keys.size()-1];

    texmap[key] = t;

    return "ok";
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
