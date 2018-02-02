#include "savefile.h"
#include "sprite.h"

std::vector<Sprite*> SaveFile::sprites_ = std::vector<Sprite*>();

void SaveFile::AddSprite(Sprite* s)
{
    sprites_.push_back(s);
}

void SaveFile::Write(const std::string& fn)
{
    json j;

    std::ofstream fp;
    fp.open(fn);
    if (fp.is_open())
    {
        fp << j.dump() << std::endl;
        fp.close();
    }
    else
    {
        std::cout << "Cannot open file: " << fn << std::endl;
    }

    j["sprites"] = {};

    uint32_t i = 0;
    for (auto& e : sprites_)
    {
        j["sprites"][i++] = {
            {"x", e->x},
            {"y", e->y},
            {"texture", ""}
        };
    }
}

void SaveFile::Read(const std::string& fn)
{
    std::ifstream i(fn);
    json j;
    i >> j;
    i.close();
}
