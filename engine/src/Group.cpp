#include "Group.hpp"
#include "Sprite.hpp"
#include "Camera.hpp"
#include "Assets.hpp"
#include "Util.hpp"
#include <iostream>

using json = nlohmann::json;

namespace engine {

    Group::Group()
	{
		x = 0;
		y = 0;
        sx = 0.0f;
        sy = 0.0f;
		visible = true;
    }

    Group::~Group()
	{

    }

    void Group::init(Context& ctx)
    {

    }

    void Group::init_from_json(const std::string& fn)
	{
        json o = Util::loadJson(fn);

        if (o.find("entry") != o.end())
		{

        }

        if (o.find("sprites") != o.end())
		{
            for (const auto& e : o["sprites"])
			{
                // assume sprite object has all required fields
                float nx = (float)e["x"];
                float ny = (float)e["y"];
                std::string name = e["name"];
                std::string texture = e["texture"];
                bool solid = e["solid"];
                std::cout << "group: solid=" << solid << std::endl;

                // test initialize
                Sprite* temp = new Sprite();
                temp->dynamic = true;
                temp->x = nx;
                temp->y = ny;
                temp->setSolid(solid);
                temp->setTexture(Assets::getTexture(texture));
                renderList.push_back(temp);
            }
        }
    }

    Sprite* Group::get_sprite_by_name(const std::string& name)
	{
        for (auto& e : renderList)
		{
            if (e->name == name)
			{
                return e;
            }
        }
        return nullptr;
    }

    Sprite* Group::getSpriteAtLocation(float nx, float ny) {
        sort();
        for (auto& e : renderList) {
            if (
                nx >= e->x &&
                nx <= e->x + e->w &&
                ny >= e->y &&
                ny <= e->y + e->h
            ) {
                return e;
            }
        }

        return nullptr;
    }

    void Group::queryAll() {
        for (auto& e : renderList) {
            e->queryTexture();
        }
    }

    void Group::add(Sprite& s)
    {
        s.setParent(this);
        renderList.push_back(&s);
    }

    void Group::add(Sprite* a) {
        a->setParent(this);
        renderList.push_back(a);
    }

    void Group::remove(Sprite* s) {
        auto pos = std::find(renderList.begin(), renderList.end(), s);
        renderList.erase(pos);
    }

    void Group::update(float delta) {
		if (!visible) return;
        /*std::vector<Sprite*>::iterator it;
        for (it = renderList.begin(); it != renderList.end(); it++)
        {
            Sprite* current = *it;
            current->update(delta);
        }*/
        for (auto& e : renderList) {
            e->update(delta);
        }
    }

    void Group::sort() {
        std::sort(renderList.begin(), renderList.end(),
            [] (Sprite* a, Sprite* b) {return a->y < b->y;});
    }

    void Group::draw(Context& ctx) {
		if (!visible) return;
        for (auto& e : renderList) {
            e->draw(ctx);
        }
    }

    void Group::draw(Context& ctx, Camera& c)
    {
        if (!visible)
        {
            return;
        }

        for (auto& e : renderList)
        {
            e->draw(ctx, c);
        }
    }

    /*void Group::draw(Object& obj, Context& ctx) {
		if (!visible) return;
        for (auto& e : renderList) {
            e->draw(obj, ctx);
        }
    }*/

    void Group::draw(Camera& c, Context& ctx)
    {
        if (!visible) return;
        for (auto& e : renderList)
        {
            e->draw(ctx, c);
        }
    }

    std::vector<Sprite*> Group::getSprites() {
        return renderList;
    }

    void Group::destroy() {
        for (auto& e : renderList) {
            if (e->dynamic) {
                printf("deleting sprite\n");
                delete e;
            }
        }
    }

	void Group::setDebug(bool value)
	{
		for (auto& e : renderList)
		{
			//e->setDebug(value);
		}
	}

	void Group::setVisible(bool value)
	{
		visible = value;
	}

	bool Group::isVisible()
	{
		return visible;
	}
}
