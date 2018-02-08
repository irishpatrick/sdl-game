#ifndef IMAGETEXT_H
#define IMAGETEXT_H

#include <string>
#include <cstring>
#include <cstdlib>
#include <SDL.h>

#include "entity.h"

class ImageText: public Entity
{
public:
    ImageText();
    ImageText(const std::string&);
    ~ImageText();

    void setText(const std::string&);

private:
    std::string str_;
    char* buffer_;
};

#endif /* IMAGETEXT_H */
