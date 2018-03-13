#include "savefile.h"

vector<engine::Sprite*> SaveFile::sprites_ = vector<engine::Sprite*>();

void SaveFile::AddSprite(engine::Sprite* s)
{
    sprites_.push_back(s);
}

void SaveFile::Write(const string& fn)
{
    json j;

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

void SaveFile::Read(const string& fn)
{
    ifstream i(fn);
    json j;
    i >> j;
    i.close();
}
