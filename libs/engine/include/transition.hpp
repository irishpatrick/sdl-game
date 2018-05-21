#pragma once

#include <cstdint>

namespace engine {

class Context;

enum Type {DUMMY, FADE};

class Transition {
public:
    Transition(Context*);
    ~Transition();

    void start(Type, uint32_t, uint32_t, uint32_t);
    void update();

private:
    void fill(uint8_t);

    uint32_t initial;
    uint32_t attack;
    uint32_t sustain;
    uint32_t release;
    bool running;
    Type type;
    Context* ctx;
};

}
