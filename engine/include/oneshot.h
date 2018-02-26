#ifndef ONESHOT_H
#define ONESHOT_H

#include <cstdio>

class OneShot
{
public:
    OneShot();
    ~OneShot();

    void check(bool);
    bool fire();

private:
    bool state;
    bool reset;
};

#endif /* ONESHOT_H */
