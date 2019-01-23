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
    map.loadMap()
}

void MapTest::update(float delta)
{

}

void MapTest::render(engine::Context& ctx)
{

}
