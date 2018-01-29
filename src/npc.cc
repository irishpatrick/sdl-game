#include "npc.h"
#include "util.h"

Npc::Npc()
{

}
Npc::~Npc()
{

}

void Npc::Json(const std::string& fn)
{
    std::ifstream in(fn);
    if (!in)
    {
        return;
    }
    nlohmann::json o;
    in >> o;

    x = o["x"];
    y = o["y"];

    if (Util::JsonExists(o, "dialogue"))
    {
        for (std::string line : o["dialogue"])
        {
            dialogue_.push_back(line);
        }
    }
}
