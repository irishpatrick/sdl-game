#include "Textbox.hpp"
#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>

Textbox::Textbox() :
    Sprite(),
    currentLine(-1)
{
    Sprite::setVisible(false);
}

Textbox::~Textbox()
{
}

void Textbox::init()
{
    Context& ctx = MyEngine::getContext();
    window.create(ctx, ctx.getWidth() - 60, 60);
}

void Textbox::fillDialogue(const std::string& str)
{
    // split string into words
    /*std::vector<std::string> words;
    boost::split(words, str, [](char c){return c == ' ';});
    int max_words = 5;
    int wc;
    Text* cur = nullptr;
    std::stringstream builder;
    for (auto& e : words)
    {
        if (wc == 0)
        {
            cur = new Text();
            lines.push_back(cur);
        }
        else if (wc < max_words)
        {
            builder << e;
            builder << " ";
        }
        else
        {
            std::cout << "creating line \"" << builder.str() << "\"" << std::endl;
            cur->create(MyEngine::getContext(), builder.str());
            builder.clear();
            wc = -1;
        }
        ++wc;
    }
    if (wc != 0)
    {
        cur->create(MyEngine::getContext(), builder.str());
    }*/
    Text* t = new Text();
    lines.push_back(t);
    t->create(MyEngine::getContext(), str);
}

void Textbox::play()
{
    ++currentLine;
    std::cout << "currentLine = " << currentLine << std::endl;
    std::cout << "lines.size() = " << lines.size() << std::endl;
    if (currentLine < lines.size())
    {
        //std::cout << "set visible" << std::endl;
        Sprite::setVisible(true);
    }
    else
    {
        std::cout << "hide" << std::endl;
        Sprite::setVisible(false);
        currentLine = -1;
    }
}

void Textbox::reset()
{
    std::cout << "deleting " << lines.size() << " lines" << std::endl;
    for (auto& e : lines)
    {
        if (e != nullptr)
        {
            delete e;
        }
    }
    lines.clear();
}

void Textbox::draw(float ex)
{
    if (!visible) return;
    
    Context& ctx = MyEngine::getContext();
    window.draw(ctx, ex, Point(x, y));
    lines[currentLine]->draw(ctx, ex, Point(10 + x, 10 + y));
}
