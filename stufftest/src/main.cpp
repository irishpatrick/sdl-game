#include <iostream>
#include <stuff.hpp>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

int main()
{
    std::cout << "hello, world" << std::endl;
    fs::path fn(fs::current_path() / "assets" / "test.stf");

    stf::Loader loader;
    loader.open(fn.generic_string());
    std::cout << "get number" << std::endl;
    //std::flush(std::stdout);
    stf::Section* section = loader.getSection("section1");
    if (section == nullptr)
    {
        std::cout << "section was null" << std::endl;
    }
    stf::Entry* entry = section->getLine(0);
}
