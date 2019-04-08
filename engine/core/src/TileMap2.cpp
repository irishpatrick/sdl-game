#include "TileMap2.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

enum MODE {INFO=0, MAP=1, NONE=-1};

namespace engine
{
    TileMap2::TileMap2()
    {

    }

    TileMap2::~TileMap2()
    {

    }

    void TileMap2::open(const std::string& fn)
    {
        std::ifstream fp;
        fp.open(fn);

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
                    if (parts[1] == "info")
                    {
                        mode = INFO;
                    }
                    if (parts[1] == "map")
                    {
                        mode = MAP;
                    }
                }
                else if (boost::starts_with(line, "end"))
                {
                    mode = NONE;
                }
            }
            else if (mode == INFO)
            {
                parts.clear();
                boost::split(parts, line, boost::is_any_of(" "));
                if (parts[0] == "width")
                {
                    try
                    {
                        w = boost::lexical_cast<uint32_t>(parts[1]);
                    }
                    catch (boost::bad_lexical_cast)
                    {

                    }
                }
                else if (parts[0] == "height")
                {
                    try
                    {
                        h = boost::lexical_cast<uint32_t>(parts[1]);
                    }
                    catch (boost::bad_lexical_cast)
                    {

                    }
                }
                else if (parts[0] == "texture")
                {
                    try
                    {
                        
                    }
                    catch (boost::bad_lexical_cast)
                    {

                    }
                }
            }
            else if (mode == MAP)
            {

            }
        }
    }
}