#include "MapTest.hpp"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

MapTest::MapTest() : State()
{

}

MapTest::~MapTest()
{

}

void MapTest::init(engine::Context& ctx)
{
    //map.loadMap((fs::current_path() / "assets" / "tilemap-test.json").generic_string());
}

void MapTest::update(float delta)
{

}

void MapTest::render(engine::Context& ctx)
{

}
