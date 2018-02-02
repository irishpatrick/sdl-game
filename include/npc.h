#ifndef NPC_H
#define NPC_H

#include <vector>
#include <string>
#include <fstream>
#include <json.hpp>

#include "sprite.h"

class Text;

class Npc: public Sprite
{
public:
    Npc();
    ~Npc();

    void Json(const std::string&);

private:
    std::vector<std::string> dialogue_;
    Text* text_;
};

#endif /* NPC_H */
