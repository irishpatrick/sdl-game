#include "Menu.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

Menu::Menu() :
    Sprite(),
    choice(0)
{
    visible = false;
    bgcolor.setRGB(1.0, 1.0, 1.0);
    txtcolor.setRGB(0.0, 0.0, 0.0);
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

void Menu::init(Context& ctx)
{
    // create window
    window.create(ctx, 100, 100);
    cairo_t* cr = window.getCairo();
    // draw window
    Color_RGB rgb = bgcolor.getRGB();
    cairo_set_source_rgb(cr, rgb.r.f, rgb.g.f, rgb.b.f);
    cairo_rectangle(cr, 0, 0, 100, 100);
    cairo_fill(cr);
    // draw border
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_rectangle(cr, 0, 0, 100, 100);
    cairo_stroke(cr);

    // create cursor
    int s = 8;
    cursor.create(ctx, s, s);
    cr = cursor.getCairo();
    
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_arc(cr, s/2, s/2, s/2, 0, 2.0 * M_PI);
    cairo_fill(cr);
}

void Menu::pushOption(Context& ctx, const std::string& str)
{
    Text* addition = new Text();
    addition->setColor(txtcolor);
    addition->create(ctx, str);
    opts.push_back(addition);
}

void Menu::draw(Context& ctx, float ex)
{
    if (!visible) return;

    window.draw(ctx, ex, Point(x, y));
    int r = 0;
    for (auto& e : opts)
    {
        e->draw(ctx, ex, Point(14 + x, 10 + y + (24 * r)));
        ++r;
    }
    cursor.draw(ctx, ex, Point(4 + x, 4 + 10 + y + (24 * choice)));
}

void Menu::moveCursor(int offset)
{
    int next = choice + offset;
    if (next < 0)
    {
        next = 0;
    }
    else if (next > opts.size() - 1)
    {
        next = opts.size() - 1;
    }
    choice = next;
}

int Menu::getChoice()
{
    return choice;
}