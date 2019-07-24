#include "Court.hpp"
#include "Player.hpp"
#include "Ball.hpp"

void Court::init(Context& ctx)
{
    w = ctx.getWidth();
    h = ctx.getHeight();

    in_bounds = BoundingBox(x + w / 10, y + w / 10, w - w / 5, h - w / 5);

    Canvas canvas;
    std::cout << "create canvas\n";
    canvas.create(ctx, ctx.getWidth(), ctx.getHeight());
    // draw court
    cairo_t* cr = canvas.getCairo();
    cairo_surface_t* surf = canvas.getCairoSurface();
    
    // background
    cairo_set_source_rgb(cr, 0.208, 0.671, 0.357);
    cairo_rectangle(cr, 0, 0, ctx.getWidth(), ctx.getHeight());
    cairo_fill(cr);

    // bounds
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_set_line_width(cr, 4.0);
    cairo_rectangle(cr, in_bounds.x, in_bounds.y, in_bounds.w, in_bounds.h);
    
    cairo_move_to(cr, in_bounds.x, in_bounds.y + in_bounds.h / 2);
    cairo_line_to(cr, in_bounds.x + in_bounds.w, in_bounds.y + in_bounds.h / 2);

    cairo_rectangle(cr, in_bounds.x, in_bounds.y + 3 * in_bounds.h / 16, in_bounds.w, 10 * in_bounds.h / 16);
    
    cairo_move_to(cr,
        in_bounds.x + in_bounds.w / 2,
        in_bounds.y + 3 * in_bounds.h / 16
    );
    cairo_line_to(cr,
        in_bounds.x + in_bounds.w / 2,
        in_bounds.y + 13 * in_bounds.h / 16
    );

    cairo_stroke(cr);

    Texture* tex = canvas.toTexturePtr(ctx);
    Assets::registerTexture(ctx, tex, "court");
    texture = Assets::getTexture("court");
}

int Court::judge(Ball* ball)
{
    return 0;
}

void Court::update(Context& ctx, float delta)
{
}

void Court::contain(Player* p)
{
    if (p->x < 0)
    {
        p->x = 0;
    }
    else if (p->x + p->w > w)
    {
        p->x = w - p->w;
    }
}
