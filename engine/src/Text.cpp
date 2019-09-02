#include "Text.hpp"
#include <sstream>
#include <cmath>
#include <pango/pangocairo.h>

namespace engine
{
    Text::Text() :
        Canvas(),
        fontsize(12),
        fontmod(""),
        fonttype("Times New Roman")
    {
        color.setRGB(0.0, 0.0, 0.0);
    }

    Text::~Text()
    {
    }

    std::string Text::genFontString()
    {
        std::stringstream ss;
        ss  << fonttype << fontmod << std::to_string(fontsize);
        return ss.str();
    }

    void Text::create(Context& ctx, const std::string& str)
    {
        Canvas::create(ctx, 1024, 1024);
        cairo_t* cr = Canvas::getCairo();

        PangoLayout* layout;
        PangoFontDescription* desc;

        layout = pango_cairo_create_layout(cr);
        pango_layout_set_text(layout, str.c_str(), -1);
        desc = pango_font_description_from_string(genFontString().c_str());
        pango_layout_set_font_description(layout, desc);
        pango_font_description_free(desc);

        //cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
        //cairo_paint(cr);
        Color_RGB rgb = color.getRGB();
        cairo_set_source_rgb(cr, rgb.r.f, rgb.g.f, rgb.b.f);
        pango_cairo_show_layout(cr, layout);

        g_object_unref(layout);
    }

    void Text::setColor(Color c)
    {
        color = c;
    }
}