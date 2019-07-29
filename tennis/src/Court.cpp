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

    // draw net
    int stretch = 10;
    cairo_set_source_rgb(cr, 0.2, 0.2, 0.2);
    cairo_set_line_width(cr, 4.0);
    cairo_move_to(cr, in_bounds.x - stretch, in_bounds.y + 7.0 * in_bounds.h / 16.0);
    cairo_line_to(cr, in_bounds.x + stretch + in_bounds.w, in_bounds.y + 7.0 * in_bounds.h / 16.0);
    cairo_line_to(cr, in_bounds.x + in_bounds.w, in_bounds.y + in_bounds.h / 2.0);
    cairo_line_to(cr, in_bounds.x, in_bounds.y + in_bounds.h / 2);
    cairo_close_path(cr);

    cairo_stroke(cr);

    cairo_set_line_width(cr, 2.0);
    int i;
    int num_h = 8;
    int num_v = 20;
    float m = fabs((in_bounds.y + in_bounds.h / 2.0 - (in_bounds.y + 7.0 * in_bounds.h / 16.0)) / (in_bounds.x - (in_bounds.x - stretch)));
    float dy = (in_bounds.y + in_bounds.h / 2.0 - (in_bounds.y + 7.0 * in_bounds.h / 16.0));
    for (i = 0; i < num_h; ++i)
    {
        float step = (i + 1) * (dy / (num_h + 1));
        float y = (in_bounds.y + in_bounds.h / 2) - step;
        float x = in_bounds.x - (step / m);
        cairo_move_to(cr, x, y);
        x = in_bounds.x + in_bounds.w + (step / m);
        cairo_line_to(cr, x, y);
    }

    for (i = 0; i < num_v; ++i)
    {
        float step = (i + 1) * (in_bounds.w / (num_v + 1));
        float y = in_bounds.y + in_bounds.h / 2;
        float x = in_bounds.x + step;
        cairo_move_to(cr, x, y);
        x = x + stretch * ((2 * ((float)i / num_v)) - 1.0);
        y = in_bounds.y + 7.0 * in_bounds.h / 16.0;
        cairo_line_to(cr, x, y);
    }

    cairo_stroke(cr);

    canvas.update();

    texture = new Texture(ctx, *canvas.getTexture());
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
