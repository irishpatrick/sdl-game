#include <iostream>
#include <stf.hpp>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

int main()
{
    std::cout << "hello, world" << std::endl;
    fs::path fn(fs::current_path() / "assets" / "test.stf");

    stf::Loader loader;
    loader.open(fn.generic_string());
}
