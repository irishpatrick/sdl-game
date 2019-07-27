#include "Court.hpp"
#include "Player.hpp"
#include "Ball.hpp"

void Court::init(Context& ctx)
{
    w = ctx.getWidth();
    h = ctx.getHeight();

    in_bounds = BoundingBox(x + w / 10, y + w / 10, w - w / 5, h - w / 5);

    Canvas canvas;
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
    
    cairo_move_to(cr, 
        (double)(in_bounds.x), 
        (double)in_bounds.y + in_bounds.h / 2.0f
    );

    cairo_line_to(cr, 
        (double)in_bounds.x + in_bounds.w, 
        (double)in_bounds.y + in_bounds.h / 2.0f
    );

    cairo_rectangle(cr, 
        (double)in_bounds.x, 
        (double)in_bounds.y + 3.0f * in_bounds.h / 16.0f, 
        (double)in_bounds.w, 
        (double)10.0f * in_bounds.h / 16.0f
    );
    
    cairo_move_to(cr,
        (double)in_bounds.x + in_bounds.w / 2.0f,
        (double)in_bounds.y + 3 * in_bounds.h / 16.0f
    );

    cairo_line_to(cr,
        (double)in_bounds.x + in_bounds.w / 2.0f,
        (double)in_bounds.y + 13.0f * in_bounds.h / 16.0f
    );

    cairo_stroke(cr);

    texture = canvas.getTexture();
    // don't forget to update
    texture->update();
}

int Court::judge(Ball* ball)
{
    if (ball->x < in_bounds.x)
    {
        ball->x = in_bounds.x;
        ball->xvel = 0;
    }
    else if (ball->x > in_bounds.x + in_bounds.w)
    {
        ball->x = in_bounds.x + in_bounds.w;
        ball->xvel = 0;
    }

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

BoundingBox& Court::getBounds()
{
    return in_bounds;
}
