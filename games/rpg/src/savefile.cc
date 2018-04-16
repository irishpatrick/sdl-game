#include "savefile.h"

vector<engine::Sprite*> SaveFile::sprites = vector<engine::Sprite*>();

void SaveFile::AddSprite(engine::Sprite* s)
{
    sprites.push_back(s);
}

void SaveFile::Write(const string& fn)
{
    json j;

    j["sprites"] = {};

    uint32_t i = 0;
    for (auto& e : sprites)
    {
        j["sprites"][i++] = {
            {"x", e->x},
            {"y", e->y},
            {"texture", ""}
        };
    }

    ofstream fp;
    fp.open(fn);
    if (fp.is_open())
    {
        fp << j.dump() << endl;
        fp.close();
    }
    else
    {
        cout << "Cannot open file: " << fn << endl;
    }
}

void SaveFile::Read(const string& fn)
{
    ifstream i(fn);
    json j;
    i >> j;
    i.close();
}
