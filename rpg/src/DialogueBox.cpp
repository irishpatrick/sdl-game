#include "DialogueBox.hpp"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

void DialogueBox::init(engine::Context& ctx, const std::string& fn)
{
	Group::init(ctx);
	text.init(ctx, (fs::current_path() / "assets" / "font.ttf").generic_string(), 22, 10);

	textBox.setTexture(engine::Assets::getTexture("dialoguebox.png"));
	textBox.w = (int) ((float)ctx.getWidth() * 0.92f); 
	textBox.h = (int) ((float)ctx.getHeight() * 0.3f);
	textBox.x = ctx.getWidth() / 2 - (textBox.w / 2);
	textBox.y = (ctx.getHeight() - 32) - textBox.h;

	//text.x = 20;
	//text.y = 768 - 400;

	//std::cout << "IMPORTANT INFO textBox.y + 10 = " << textBox.y + 10 << std::endl;

	text.x = textBox.x + 50;
	text.y = textBox.y + 50;

	text.addLine("line test that really does go on for a while");
	text.addLine("other line test");
	text.next();

	add(&textBox);
	add(&text);
}

void DialogueBox::update(float delta)
{
	text.update();
	textBox.update(delta);
}

/*void DialogueBox::draw(engine::Context& ctx)
{
	textBox.draw(ctx);
	text.draw(ctx);
}*/