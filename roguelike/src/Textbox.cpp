#include "Textbox.hpp"

int Textbox::currentLine = -1;
Canvas Textbox::window;
std::vector<Text*> Textbox::lines;
int Textbox::x = 0;
int Textbox::y = 0;
bool Textbox::visible = false;

void Textbox::init()
{
    Context& ctx = MyEngine::getContext();
    window.create(ctx, ctx.getWidth() - 60, 60);
    x = 30;
    y = ctx.getHeight() - 60 - 30;

    cairo_t* cr = window.getCairo();
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_rectangle(cr, 0, 0, window.getWidth(), window.getHeight());
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_set_line_width(cr, 2.0);
    cairo_rectangle(cr, 0, 0, window.getWidth(), window.getHeight());
    cairo_stroke(cr);
}

void Textbox::fillDialogue(const std::string& str)
{
    Text* t = new Text();
    lines.push_back(t);
    t->create(MyEngine::getContext(), str);
}

void Textbox::play()
{
    ++currentLine;
    if (currentLine < (int)lines.size())
    {
        visible = true;
    }
    else
    {
        visible = false;
        currentLine = -1;
    }
}

void Textbox::reset()
{
    for (auto& e : lines)
    {
        if (e != nullptr)
        {
            delete e;
        }
    }
    lines.clear();
}

void Textbox::draw()
{
    if (!visible) return;
    
    Context& ctx = MyEngine::getContext();
    window.draw(ctx, 0.0f, Point(x, y));
    lines[currentLine]->draw(ctx, 0.0f, Point(10 + x, 10 + y));
}

bool Textbox::isVisible()
{
    return visible;
}
