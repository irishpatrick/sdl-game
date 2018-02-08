#include "imagetext.h"

ImageText::ImageText(): ImageText("")
{

}

ImageText::ImageText(const std::string& str)
{
    str_ = str;
    buffer_ = (char*)malloc(str_.size() * sizeof(char));
}

ImageText::~ImageText()
{
    if (buffer_ != nullptr)
    {
        free(buffer_);
    }
}

void ImageText::setText(const std::string& str)
{
    str_ = str;
    buffer_ = (char*)malloc(str_.size() * sizeof(char));
}
