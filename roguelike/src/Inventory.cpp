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
    tilePad(10),
    numItems(0)
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

    actions.init(ctx);
    actions.pushOption(ctx, "Use");
    actions.pushOption(ctx, "Equip");
    actions.pushOption(ctx, "Drop");

    actions.x = 32;
    actions.y = 32;
}

void Inventory::fill(Player* p)
{
    player = p;
    int n = 0;
    int r;
    int c;
    numItems = player->getInventory().size();
    for (auto& e : player->getInventory())
    {
        r = n / gridW;
        c = n % gridW;

        //std::cout << "place item at <" << r << "," << c << ">" << std::endl;

        grid[r][c] = &e;

        ++n;
    }
}

Item* Inventory::getSelection()
{
    int index = selection.x + (selection.y * gridW);
    if (selection.x > gridW || index > numItems)
    {
        return nullptr;
    }
    return grid[(int)selection.y][(int)selection.x];
}

void Inventory::update()
{
    Keyboard::poll();

    if (!actions.isVisible())
    {
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
        selection.x = (int)fmin(selection.x, (numItems % gridW) - 1);
        selection.y = (int)fmin(selection.y, numItems / gridH);

        actions.x = 32 + (tilePad * (selection.x + 1)) + (tileSize * selection.x);
        actions.y = 32 + (tilePad * (selection.y + 1)) + (tileSize * selection.y);

        if (Keyboard::isPressed("p"))
        {
            /*Item* selection = getSelection();
            if (selection != nullptr)
            {
                std::cout << "selection: " << getSelection()->getName() << std::endl;
            }*/
            actions.setVisible(true);
        }

        cursor.update();
        cursor.x = (tilePad * (selection.x + 1)) + (tileSize * selection.x);
        cursor.y = (tilePad * (selection.y + 1)) + (tileSize * selection.y);
    }
    else
    {
        if (Keyboard::isPressed("escape"))
        {
            actions.setVisible(false);
        }
        else if (Keyboard::isPressed("w"))
        {
            actions.moveCursor(-1);
        }
        else if (Keyboard::isPressed("s"))
        {
            actions.moveCursor(1);
        }
        else if (Keyboard::isPressed("p"))
        {
            int cur = actions.getChoice();
            Item* sel = getSelection();
            if (cur == 0)
            {
                std::cout << "use item " << sel->getName() << std::endl;
            }
            else if (cur == 1)
            {
                std::cout << "equip item " << sel->getName() << std::endl;
            }
            else if (cur == 2)
            {
                std::cout << "drop item " << sel->getName() << std::endl;
            }
            actions.setVisible(false);
        }

    }
}

void Inventory::render(float ex)
{
    if (numItems < 1)
    {
        return;
    }
    cursor.draw(MyEngine::getContext());
    //std::cout << "draw inventory" << std::endl;
    if (player == nullptr)
    {
        //std::cout << "player null, cannot draw" << std::endl;
        return;
    }

    int n = numItems;
    int i;
    int r;
    int c;
    for (i = 0; i < n; ++i)
    {
        r = i / gridW;
        c = i % gridW;
        Item* item = grid[r][c];
        if (item == nullptr)
        {
            std::cout << "item was null" << std::endl;
            break;
        }
        Texture* t = item->getTexture();
        if (t == nullptr)
        {
            std::cout << "texture was null" << std::endl;
            break;
        }
        t->display((tilePad * (c + 1)) + (tileSize * c), (tilePad * (r + 1)) + (tileSize * r));
    }

    actions.draw(ex);
}
