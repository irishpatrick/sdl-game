#include "plane.h"
#include "config.h"

Plane::Plane(): Projectile()
{
    max_speed = Config::getPlaneSpeed();
}

Plane::~Plane()
{

}
