#include "Court.hpp"
#include "Player.hpp"
#include "Ball.hpp"

double half(double val)
{
    return val / 2.0;
}

void to_cr(float* val)
{
    *val = roundf(*val) + 1.0f;
}

void to_cr(float* x, float* y)
{
    *x = roundf(*x) + 1.0f;
    *y = roundf(*y) + 1.0f;
}

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
    
    // center line
    /*cairo_move_to(cr, 
        (double)(in_bounds.x), 
        (double)in_bounds.y + in_bounds.h / 2.0f
    );

    cairo_line_to(cr, 
        (double)in_bounds.x + in_bounds.w, 
        (double)in_bounds.y + in_bounds.h / 2.0f
    );*/

    cairo_rectangle(cr, 
        (double)in_bounds.x, 
        (double)in_bounds.y + 3.0f * in_bounds.h / 16.0f, 
        (double)in_bounds.w, 
        (double)10.0f * in_bounds.h / 16.0f
    );
    
    cairo_move_to(cr,
        (double)in_bounds.x + half(in_bounds.w),
        (double)in_bounds.y + 3 * in_bounds.h / 16.0f
    );

    cairo_line_to(cr,
        (double)in_bounds.x + half(in_bounds.w),
        (double)in_bounds.y + 13.0f * in_bounds.h / 16.0f
    );

    cairo_stroke(cr);

    // draw net
    /*int stretch = 10;
    double ratio = 7.5 / 16.0;
    cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
    cairo_set_line_width(cr, 3.0);
    cairo_move_to(cr, in_bounds.x - stretch, in_bounds.y + (in_bounds.h * ratio));
    cairo_line_to(cr, in_bounds.x + stretch + in_bounds.w, in_bounds.y + (in_bounds.h * ratio));
    cairo_line_to(cr, in_bounds.x + in_bounds.w, in_bounds.y + half(in_bounds.h));
    cairo_line_to(cr, in_bounds.x, in_bounds.y + half(in_bounds.h));
    cairo_close_path(cr);

    cairo_stroke(cr);

    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_set_line_width(cr, 1.0);
    int i;
    int num_h = 4;
    int num_v = 20;
    float m = fabs((in_bounds.y + half(in_bounds.h) - (in_bounds.y + (in_bounds.h * ratio))) / (in_bounds.x - (in_bounds.x - stretch)));
    float dy = (in_bounds.y + half(in_bounds.h) - (in_bounds.y + (in_bounds.h * ratio)));
    for (i = 0; i < num_h; ++i)
    {
        float step = (i + 1) * (dy / (num_h + 1));
        float y = (in_bounds.y + half(in_bounds.h)) - step;
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
        y = in_bounds.y + (in_bounds.h * ratio);
        cairo_line_to(cr, x, y);
    }

    cairo_stroke(cr);
    */

    // draw other net
    float height = 30;
    float width = height / 4;

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 2);

    int num_x = 30;
    int num_y = 6;
    int i;

    float xstep = (in_bounds.w + (width * 2)) / (num_x + 1);
    float ystep = height / (num_y + 1);

    for (i = 0; i < num_x; ++i)
    {
        float x = in_bounds.x - width + ((i + 1) * xstep);
        float y = in_bounds.y + half(in_bounds.h) - height;
        to_cr(&x, &y);
        cairo_move_to(cr, x, y);
        y = (in_bounds.y + half(in_bounds.h));
        to_cr(&y);
        cairo_line_to(cr, x, y);
    }

    for (i = 0; i < num_y; ++i)
    {
        float x = in_bounds.x - width;
        float y = in_bounds.y + half(in_bounds.h) - height + ((i + 1) * ystep);
        to_cr(&x, &y);
        cairo_move_to(cr, x, y);
        //y = in_bounds.y + half(in_bounds.h);
        x = in_bounds.x + in_bounds.w + width;
        to_cr(&x);
        cairo_line_to(cr, x, y);
    }

    cairo_stroke(cr);

    // draw posts
    cairo_set_source_rgb(cr, 0, (221.0 / 255.0), 1);
    cairo_set_line_width(cr, width);
    cairo_move_to(cr, in_bounds.x - width, in_bounds.y + half(in_bounds.h) + half(width));
    cairo_line_to(cr, in_bounds.x - width, in_bounds.y + half(in_bounds.h) - height - half(width));
    cairo_move_to(cr, in_bounds.x + in_bounds.w + width, in_bounds.y + half(in_bounds.h) + half(width));
    cairo_line_to(cr, in_bounds.x + in_bounds.w + width, in_bounds.y + half(in_bounds.h) - height - half(width));
    cairo_stroke(cr);

    // draw top
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_set_line_width(cr, width);
    cairo_move_to(cr, in_bounds.x - width + half(width), in_bounds.y + half(in_bounds.h) - height);
    cairo_line_to(cr, in_bounds.x + in_bounds.w + width - half(width), in_bounds.y + half(in_bounds.h) - height);
    cairo_stroke(cr);

    // shadow
    cairo_set_source_rgba(cr, 0, 0, 0, 0.2);
    cairo_set_line_width(cr, width);
    cairo_move_to(cr, in_bounds.x - width + half(width), in_bounds.y + half(in_bounds.h));
    cairo_line_to(cr, in_bounds.x + in_bounds.w + width - half(width), in_bounds.y + half(in_bounds.h));
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
