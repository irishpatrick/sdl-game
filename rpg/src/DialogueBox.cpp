#include "DialogueBox.hpp"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

void DialogueBox::init(engine::Context& ctx, const std::string& fn)
{
	Group::init(ctx);
	text.init(ctx, (fs::current_path() / "assets" / "font.ttf").generic_string(), 20, 20);

	textBox.setTexture(engine::Assets::getTexture("dialoguebox.png"));
	textBox.x = ctx.getWidth() / 2 - (textBox.w / 2);
	textBox.h = (ctx.getHeight() - 32) - textBox.h;

	text.x = textBox.x + 10;
	text.y = textBox.y + 10;
}

void DialogueBox::update(float delta)
{
	text.update();
	textBox.update(delta);
}

void DialogueBox::draw(engine::Context& ctx)
{
	textBox.draw(ctx);
	text.draw(ctx);
}