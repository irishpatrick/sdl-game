#ifndef SIGMOID_H
#define SIGMOID_H

class Sigmoid {

public:
    Sigmoid();
    Sigmoid(float, float, float);
    ~Sigmoid();

    float solve(float);

    float L;
    float xn;
    float k;
};

#endif /* SIGMOID_H */
