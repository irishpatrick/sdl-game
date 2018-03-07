#include "sigmoid.h"
#include <cmath>

Sigmoid::Sigmoid(float a, float b, float c) {
    xn = a;
    L = b;
    k = c;
}

Sigmoid::Sigmoid(): Sigmoid(0,1,1) {

}

Sigmoid::~Sigmoid() {

}

float Sigmoid::solve(float x) {
    return L / (1 + exp(-k * (x - xn)));
}
