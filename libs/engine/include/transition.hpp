#pragma once

enum Type {NONE, FADE};

class Transition {
public:
    Transition();
    ~Transition();

    void start(Type, float, float, float);
    void update(float);

private:
    float attack;
    float sustain;
    float release;
    bool running;
    Type type;
};
