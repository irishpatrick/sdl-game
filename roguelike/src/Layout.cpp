#include "Layout.hpp"
#include <cstdlib>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "Tilemap.hpp"

using json = nlohmann::json;

Layout::Layout() :
    map(nullptr),
    w(-1),
    h(-1)
{

}

Layout::~Layout()
{
    if (map != nullptr)
    {
        int i;
        for (i = 0; i < h; ++i)
        {
            free(map[i]);
        }
        free(map);
    }
}

void Layout::load(const std::string& fn)
{
    std::ifstream in(fn);
    if (!in.is_open())
    {
        std::cout << "cannot open " << fn << "\n";
        return;
    }
    json o(in);
    in.close();

    if (o.find("table") == o.end() || o.find("size") == o.end() || o.find("data") == o.end())
    {
        std::cout << "bad format\n";
        return;
    }

    w = o["size"][0].get<int>();
    h = o["size"][1].get<int>();
    map = (char**)malloc(h * sizeof(char*));
    int i;
    for (i = 0; i < h; ++i)
    {
        map[i] = (char*)malloc(w * sizeof(char));
    }

    for (auto& e : o["table"])
    {
        ref.push_back(e.get<std::string>());
    }

    i = 0;
    for (auto& e : o["data"])
    {
        char c = (char)e.get<int>();
        map[i / w][i % w] = c;
        ++i;
    }
}

const std::string& Layout::get(int x, int y)
{
    return ref[(int)map[y][x]];
}

void Layout::draw(Context& ctx, float ex, Tilemap* tm)
{
    int i;
    int j;
    for (i = 0; i < h; ++i)
    {
        for (j = 0; j < h; ++j)
        {
            Sprite* s = tm->getTile(get(j, i));
            s->x = j * 32;
            s->y = i * 32;
            s->draw(ctx, ex);
        }
    }
}

int Layout::width()
{
    return w;
}

int Layout::height()
{
    return h;
}
