#include "Menu.hpp"

Menu::Menu() :
    Sprite()
{

}

Menu::~Menu()
{
    for (auto& e : opts)
    {
        if (e == nullptr)
        {
            continue;
        }

        delete e;
        e = nullptr;
    }
}

void Menu::pushOption(Context& ctx, const std::string& str)
{
    Text* addition = new Text();
    addition->create(ctx, str);
    opts.push_back(addition);
}

void Menu::draw(Context& ctx, float ex)
{
    window.draw(ctx, ex, Point(x, y));
    for (auto& e : opts)
    {
        e->draw(ctx, ex, Point(x, y));
    }
    //cursor.draw(ctx, ex, Point(x, y));
}