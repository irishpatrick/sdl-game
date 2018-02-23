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
    float tx = x - target->x;
    float ty = y - target->y;
    //float dist = sqrt(pow(tx,2) + pow(ty,2));

    if (tx > 0)
    {
        target_angle = MyUtil::deg(atan(ty / tx)) + 90 - 180;
    }
    else if (tx < 0)
    {
        target_angle = 270 + MyUtil::deg(atan(ty / tx)) - 180;
    }
    else
    {
        if (ty > 0)
        {
            target_angle = 0;
        }
        if (ty < 0)
        {
            target_angle = 180;
        }
    }

    float distl = fmod(target_angle, 360.0f);
    float distr = -360.0f + distl;

    if (distl < distr)
    {
        angle -= 100 * delta;
    }
    else if (distr < distl)
    {
        angle += 100 * delta;
    }

    printf("%f, %f\n", distl, distr);

    double drag = 100;

    xvel += (sin(MyUtil::rad(angle)) * thrust) * delta;
    yvel += (-cos(MyUtil::rad(angle)) * thrust) * delta;
    xvel -= (xvel * 0.9) * delta;
    yvel -= (yvel * 0.9) * delta;

    x += xvel * delta;
    y += yvel * delta;
}
