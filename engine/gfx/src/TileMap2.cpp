#include "TileMap2.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

enum MODE {INFO=0, MAP=1, TEX=2, NONE=-1};

namespace engine
{
    TileMap2::TileMap2()
    {
        w = 0;
        h = 0;
        tex = nullptr;
    }

    TileMap2::~TileMap2()
    {

    }

    void TileMap2::open(const std::string& fn)
    {
        std::ifstream fp;
        fp.open(fn);
        if (fp.fail())
        {
            std::cout << "couldn't open file" << std::endl;
        }

        std::string line;
        std::vector<std::string> parts;
        int mode = NONE;
        while (std::getline(fp, line))
        {   
            if (mode == NONE)
            {
                if (boost::starts_with(line, "begin "))
                {
                    parts.clear();
                    boost::split(parts, line, boost::is_any_of(" "));
                    if (boost::starts_with(parts[1], "info"))
                    {
                        mode = INFO;
                    }
                    else if (parts[1] == "map")
                    {
                        mode = MAP;
                    }
                    else if (parts[1] == "textures")
                    {
                        mode = TEX;
                    }
                }
            }
            else if (boost::starts_with(line, "end"))
            {
                mode = NONE;
                std::cout << "summary: " << std::endl;
                std::cout << "w: " << w << std::endl;
                std::cout << "h: " << h << std::endl;
                //std::cout << "tex: " << tex.getName() << std::endl;
            }
            else if (mode == INFO)
            {
                parts.clear();
                boost::split(parts, line, boost::is_any_of(" "));
                if (boost::starts_with(parts[0], "w "))
                {
                    std::cout << "hit" << std::endl;
                    try
                    {
                        w = boost::lexical_cast<uint32_t>(parts[1]);
                    }
                    catch (boost::bad_lexical_cast)
                    {
                        std::cout << "bad cast" << std::endl;
                    }
                }
                else if (boost::starts_with(parts[0], "h "))
                {
                    try
                    {
                        h = boost::lexical_cast<uint32_t>(parts[1]);
                    }
                    catch (boost::bad_lexical_cast)
                    {
                        std::cout << "bad cast" << std::endl;
                    }
                }
                else if (boost::starts_with(parts[0], "tex "))
                {
                    try
                    {
                        tex = Assets::getTexture(parts[1]);
                    }
                    catch (boost::bad_lexical_cast)
                    {
                        std::cout << "bad cast" << std::endl;
                    }
                }
            }
            else if (mode == MAP)
            {

            }
            else if (mode == TEX)
            {

            }
        }
    }
}