#ifndef IMAGEFONT_H
#define IMAGEFONT_H

class Texture;

class ImageFont
{
public:
    ImageFont();
    ~ImageFont();

private:
    Texture* tex;
};

#endif /* IMAGEFONT_H */
