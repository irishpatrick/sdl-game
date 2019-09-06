#include "Inventory.hpp"
#include "Player.hpp"
#include "Item.hpp"
#include <cstdlib>
#include <iostream>

Inventory::Inventory() :
    State(),
    gridW(0),
    gridH(0),
    tileSize(32),
    tilePad(10)
{
    setName("inventory");
}

Inventory::~Inventory()
{
    for (auto& e : grid)
    {
        if (e == nullptr)
        {
            continue;
        }
        free(e);
        e = nullptr;
    }
}

void Inventory::init()
{
    gridW = 11;
    gridH = 10;

    int i;
    for (i = 0; i < gridH; ++i)
    {
        Item** arr = (Item**)malloc(sizeof(Item*) * gridW);
        int j;
        for (j = 0; j < gridW; ++j)
        {
            arr[i] = nullptr;
        }
        grid.push_back(arr);
    }

    Context& ctx = MyEngine::getContext();
    cursor.create(ctx, tileSize, tileSize);
    cairo_t* cr = cursor.getCairo();

    cairo_set_line_width(cr, 2.0);
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_rectangle(cr, 0, 0, tileSize, tileSize);
    //cairo_stroke(cr);
    cairo_fill(cr);
}

void Inventory::fill(Player* p)
{
    player = p;
    int n = 0;
    int r;
    int c;
    for (auto& e : player->getInventory())
    {
        r = n / gridW;
        c = n % gridW;

        grid[r][c] = &e;

        ++n;
    }
}

void Inventory::update()
{
    Keyboard::poll();
    if (Keyboard::isPressed("escape") || Keyboard::isPressed("e"))
    {
        MyEngine::setCurrentState("dungeon");
    }
    if (Keyboard::isPressed("w"))
    {
        selection.y -= 1;
    }
    else if (Keyboard::isPressed("s"))
    {
        selection.y += 1;
    }
    if (Keyboard::isPressed("d"))
    {
        selection.x += 1;
    }
    else if (Keyboard::isPressed("a"))
    {
        selection.x -= 1;
    }
    selection.x = (int)fmax(0, selection.x);
    selection.y = (int)fmax(0, selection.y);
    selection.x = (int)fmin(selection.x, gridW);
    selection.y = (int)fmin(selection.y, gridH);
    cursor.update();
    cursor.x = (tilePad * (selection.x + 1)) + (tileSize * selection.x);
    cursor.y = (tilePad * (selection.y + 1)) + (tileSize * selection.y);
}

void Inventory::render(float ex)
{
    cursor.draw(MyEngine::getContext());
    //std::cout << "draw inventory" << std::endl;
    if (player == nullptr)
    {
        //std::cout << "player null, cannot draw" << std::endl;
        return;
    }
    for (auto& e : grid)
    {
        if (e == nullptr)
        {
            break;
        }
        int c;
        int r = 0;
        for (c = 0; c < gridW; ++c)
        {
            Item* i = e[c];
            if (i == nullptr)
            {
                break;
            }
            Texture* t = i->getTexture();
            if (t == nullptr)
            {
                continue;
            }
            t->display((tilePad * (c + 1)) + (tileSize * c), (tilePad * (r + 1)) + (tileSize * r));
        }
        ++r;
    }
    /*int n = 0;
    for (auto& e : player->getInventory())
    {
        Texture* t = e.getTexture();
        if (t == nullptr)
        {
            //std::cout << "null texture, cannot display" << std::endl;
            continue;
        }
        t->display((tilePad * (n + 1)) + (tileSize * n), tilePad);
        ++n;
    }*/
}