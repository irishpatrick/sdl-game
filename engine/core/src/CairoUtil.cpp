#include "CairoUtil.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

namespace engine
{
    void CairoUtil::drawVector(cairo_t* cr, uint32_t x, uint32_t y, uint32_t magnitude, double angle)
    {
        cairo_save(cr);

        double theta = (angle * M_PI) / 180.0;
        double x_component = magnitude * cos(theta);
        double y_component = magnitude * sin(theta);

        cairo_set_line_width(cr, 4);
        cairo_set_source_rgba(cr, 0, 0, 0, 1);  
        cairo_move_to(cr, x, y);
        cairo_line_to(cr, x + x_component, y + y_component);
        cairo_stroke(cr);
        
        double tick_magnitude = magnitude / 10.0;
        double tick_theta1 = theta + (M_PI / 2.0);
        double tick_theta2 = -1 * (theta + (M_PI / 2.0));
        double tick_cx_1 = tick_magnitude * cos(tick_theta1);
        double tick_cy_1 = tick_magnitude * sin(tick_theta1);
        double tick_cx_2 = tick_magnitude * cos(tick_theta2);
        double tick_cy_2 = tick_magnitude * sin(tick_theta2);

        double tip_x = x + x_component;
        double tip_y = y + y_component;

        cairo_set_source_rgba(cr, 1, 1, 1, 1);

        cairo_move_to(cr, x + x_component, y + y_component);
        cairo_line_to(cr, tip_x + tick_cx_1, tip_y + tick_cy_1);
        cairo_stroke(cr);

        cairo_move_to(cr, x + x_component, y + y_component);
        cairo_line_to(cr, tip_x + tick_cx_2, tip_y + tick_cy_2);
        cairo_stroke(cr);
    
        cairo_restore(cr);
    }
}