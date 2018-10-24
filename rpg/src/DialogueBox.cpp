#include "DialogueBox.hpp"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

void DialogueBox::init(engine::Context& ctx, const std::string& fn)
{
	Group::init(ctx);
	text.init(ctx, (fs::current_path() / "assets" / "font.ttf").generic_string(), 20, 20);
}

void DialogueBox::update(float delta)
{

}

void DialogueBox::draw(engine::Context& ctx)
{

}