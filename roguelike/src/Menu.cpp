#include "Menu.hpp"

Menu::Menu() :
    Sprite()
{
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
    cairo_set_source_rgb(cr, rgb.r.f, rgb.g.f, rgb.b.f);
    cairo_rectangle(cr, 2, 2, 97, 97);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_rectangle(cr, 4, 4, 95, 95);
    cairo_stroke(cr);
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
    window.draw(ctx, ex, Point(x, y));
    int r = 0;
    for (auto& e : opts)
    {
        e->draw(ctx, ex, Point(10 + x, 10 + y));
        ++r;
    }
    //cursor.draw(ctx, ex, Point(x, y));
}