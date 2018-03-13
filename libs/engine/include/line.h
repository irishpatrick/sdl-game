#ifndef LINE_H
#define LINE_H

namespace engine {

class Line
{
public:
    Line(float, float, float, float);
    ~Line();

    float solve(float);

private:
    float m;
    float b;
};

}

#endif /* LINE_H */
