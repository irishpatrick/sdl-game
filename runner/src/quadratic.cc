#include "quadratic.h"

Quadratic::Quadratic(): Quadratic(1,1) {

}

Quadratic::Quadratic(float amp, float duration) {
    a = amp;
    d = duration;
}

Quadratic::~Quadratic() {

}

float Quadratic::solve(float x) {
    return (4*a) / (d*d) * x * (x - d);
}
