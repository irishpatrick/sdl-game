#include "missile.h"
#include "plane.h"
#include "myutil.h"
#include "config.h"

Missile::Missile(): Projectile()
{
    thrust = Config::getMissileAcceleration();
}

Missile::~Missile()
{

}

void Missile::launch()
{
    //double min = 0.0;
    //double max = (2.0 * M_PI) * 1000;
    //int r = rand() % (int)(max - min + 1) + (int)min;

    x = 0;
    y = 0;
    printf("launch coord: %f,%f\n", x, y);
}

void Missile::setTarget(Plane* p)
{
    target = p;
}

void Missile::update(float delta)
{
    float tx = target->x - x;
    float ty = target->y - y;
    //float dist = sqrt(pow(tx,2) + pow(ty,2));

    float target_angle = 0;

    //float dist = sqrt(pow(x,2) + pow(y,2));

    if (tx > 0)
    {
        target_angle = MyUtil::deg(atan(ty / tx));
    }
    else if (tx < 0)
    {
        target_angle = MyUtil::deg(atan(ty / tx));
    }
    else
    {
        if (ty > 0)
        {
            target_angle = 180;
        }
        if (ty < 0)
        {
            target_angle = 0;
        }
    }

    float t_angle_x = cos(MyUtil::rad(target_angle));
    float t_angle_y = sin(MyUtil::rad(target_angle));
    float angle_x = cos(MyUtil::rad(angle));
    float angle_y = sin(MyUtil::rad(angle));
    //printf("%f,%f %f,%f\n", angle_x, angle_y, t_angle_x, t_angle_y);

    printf("%f, %f\n", angle, target_angle);

    if (angle_x < t_angle_x && angle_y < t_angle_y)
    {
        angle += 100 * delta;
    }
    else if (angle_x > t_angle_x && angle_y < t_angle_y)
    {
        angle -= 100 * delta;
    }
    else if (angle_x < t_angle_x && angle_y > t_angle_y)
    {
        angle += 100 * delta;
    }
    else if (angle_x > t_angle_x && angle_y > t_angle_y)
    {
        angle -= 100 * delta;
    }

    double drag = 100;

    xvel += (sin(MyUtil::rad(angle)) * thrust) * delta;
    yvel += (-cos(MyUtil::rad(angle)) * thrust) * delta;
    xvel -= (xvel * 0.9) * delta;
    yvel -= (yvel * 0.9) * delta;

    x += xvel * delta;
    y += yvel * delta;
}
