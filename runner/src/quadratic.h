#ifndef QUADRATIC_H
#define QUADRATIC_H

class Quadratic {

public:
    Quadratic();
    Quadratic(float,float);
    ~Quadratic();

    float solve(float);

    float a;
    float d;
};

#endif /* QUADRATIC_H */
