#include "Text.hpp"
#include <cmath>
#include <pango/pangocairo.h>

namespace engine
{
    Text::Text() :
        Canvas()
    {

    }

    Text::~Text()
    {
    }

    void Text::create(Context& ctx, const std::string& str)
    {
        Canvas::create(ctx, 1024, 1024);
        cairo_t* cr = getCairo();

        PangoLayout* layout;
        PangoFontDescription* desc;

        layout = pango_cairo_create_layout(cr);
        pango_layout_set_text(layout, str.c_str(), -1);
        desc = pango_font_description_from_string("Sans Bold 27");
        pango_layout_set_font_description(layout, desc);
        pango_font_description_free(desc);

        cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
        cairo_paint(cr);
        cairo_set_source_rgb(cr, 0.8, 0.1, 0.4);
        pango_cairo_show_layout(cr, layout);

        g_object_unref(layout);
    }

    /*void Text::draw(Context& ctx, float ex, Point offset)
    {

    }*/
}