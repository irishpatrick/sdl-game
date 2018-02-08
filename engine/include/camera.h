#ifndef CAMERA_H
#define CAMERA_H

class Sprite;

class Camera
{
public:
    Camera();
    ~Camera();

    void setFocus(Sprite*);
    void update(float);
    void screen(int, int);

    float x;
    float y;

private:
    int w;
    int h;
	float fx;
	float fy;
    Sprite* focus;
};

#endif /* CAMERA_H */