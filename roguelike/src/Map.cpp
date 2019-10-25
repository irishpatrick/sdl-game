#include "Map.hpp"
#include "Tile.hpp"

Map::Map() :
    Grid(),
    store(nullptr)
{

}

Map::~Map()
{

}

int Map::open(const std::string& str)
{
    store = blk_open(str.c_str());
    if (store == nullptr)
    {
        return 1;
    }

    int i;
    int j;
    for (i = 0; i < store->dimension.y; i++)
    {
        for (j = 0; j < store->dimension.x; j++)
        {
            Tile* t = new Tile();
            t->x = j * 32;
            t->y = i * 32;
            t->setTexture(Assets::getTexture(blk_get_entry(store, blk_at(store, j, i))));
            tiles.push_back(t);
        }
    }
}

void Map::draw()
{
    Context& ctx = MyEngine::getContext();

    for (auto& e : tiles)
    {
        e->draw(ctx);
    }
}
