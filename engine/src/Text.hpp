#pragma once

#include "Canvas.hpp"
#include "Context.hpp"
#include "Color.hpp"
#include "Point.hpp"
#include <string>

namespace engine
{
    class Text : public Canvas
    {
    public:
        Text();
        ~Text();

        void create(Context&, const std::string&);

    private:
        std::string genFontString();
        int fontsize;
        std::string fontmod;
        std::string fonttype;
    };
}
