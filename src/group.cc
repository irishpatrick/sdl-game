#include "group.h"

Group::Group()
{
    x = 0;
    y = 0;
    sx = 0;
    sy = 0;
    camera = nullptr;
    dynamic = false;
}

Group::~Group()
{
    
}

void Group::init(SDL_Renderer* r)
{
    
}

void Group::init_from_json(const std::string& fn)
{
	std::ifstream t(fn);
	std::string data((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	rapidjson::Document json;
	json.Parse(data.c_str());

    if (json.HasMember("entry"))
    {
        
    }

	if (json.HasMember("sprites"))
	{
		for (const auto& e : json["sprites"].GetArray())
		{
            // assume sprite object has all required fields
			float x = (float)e["x"].GetInt();
            float y = (float)e["y"].GetInt();
            std::string name = e["name"].GetString();
            std::string texture = e["texture"].GetString();

            // test initialize
            Sprite* temp = new Sprite();
            temp->dynamic = true;
            temp->x = x;
            temp->y = y;
            temp->setTexture(Assets::getTexture(texture));
            renderList.push_back(temp);
            //delete temp;
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

float Group::screenX()
{
    if (camera != nullptr)
    {
        return x + camera->x;
    }
    return x;
}

float Group::screenY()
{
    if (camera != nullptr)
    {
        return y + camera->y;
    }
    return y;
}

void Group::queryAll()
{
	for (auto& e : renderList)
	{
		e->queryTexture();
	}
}

void Group::add(Sprite* a)
{
    a->setParent(this);
    renderList.push_back(a);
}

void Group::remove(Sprite* s)
{
	auto pos = std::find(renderList.begin(), renderList.end(), s);
	renderList.erase(pos);
}

void Group::update(float delta)
{
    /*std::vector<Sprite*>::iterator it;
    for (it = renderList.begin(); it != renderList.end(); it++)
    {
        Sprite* current = *it;
        current->update(delta);
    }*/
    for (auto& e : renderList)
    {
        e->update(delta);
    }
}

void Group::setCamera(Camera* c)
{
    camera = c;
}

void Group::sort()
{
    std::sort(renderList.begin(), renderList.end(), 
        [] (Sprite* a, Sprite* b) {return a->y < b->y;});
}

void Group::draw(SDL_Renderer *r)
{
    /*std::vector<Sprite*>::iterator it;
    for (it = renderList.begin(); it != renderList.end(); it++)
    {
        Sprite* current = *it;
        current->draw(r);
    }*/
    for (auto& e : renderList)
    {
        e->draw(r);
    }
}

std::vector<Sprite*> Group::getSprites()
{
    return renderList;
}

void Group::destroy()
{
    for (auto& e : renderList)
    {
        if (e->dynamic)
        {
            printf("deleting sprite\n");
            delete e;
        }
    }
}