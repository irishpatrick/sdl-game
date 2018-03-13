#ifndef NPC_H
#define NPC_H

#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <engine.h>

using namespace std;

class Npc: public engine::Sprite
{
public:
    Npc();
    ~Npc();

    void Json(const string&);

private:
    vector<string> dialogue_;
    engine::Text* text_;
};

#endif /* NPC_H */
