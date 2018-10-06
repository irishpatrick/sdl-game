#include "Util.hpp"
#include "Sprite.hpp"
#include "Line.hpp"
#include "Group.hpp"
#include <cmath>
//#include "BoundingBox.hpp"

static bool isLoggerActive = false;

namespace engine {

	std::string Util::checkCollision(Sprite* a, Sprite* b)
	{
		if (!a->solid || !b->solid)
		{
			return "no collision";
		}
		BoundingBox abox = getAABB(a, 16.0f);
		BoundingBox bbox = getAABB(b, 16.0f);

		if (
			abox.x < bbox.x + bbox.w &&
			abox.x + abox.w > bbox.x &&
			abox.y < bbox.y + bbox.h &&
			abox.y + abox.h > bbox.y)
		{
			a->OnCollision(b);
			b->OnCollision(a);

			Line d1(
				(float)bbox.x, (float)bbox.y,
				(float)bbox.x + (float)bbox.w, (float)bbox.y + (float)bbox.h);
			Line d2(
				(float)bbox.x + (float)bbox.w, (float)bbox.y,
				(float)bbox.x, (float)bbox.y + (float)bbox.h);

			float cx = abox.x + (abox.w / 2.0f);
			float cy = abox.y + (abox.h / 2.0f);
			bool aboveD1 = cy < d1.solve(cx);
			bool aboveD2 = cy < d2.solve(cx);

			if (aboveD1 && aboveD2)
			{
				return "south";
			}
			else if (!aboveD1 && !aboveD2)
			{
				return "north";
			}
			else if (!aboveD1 && aboveD2)
			{
				return "east";
			}
			else if (aboveD1 && !aboveD2)
			{
				return "west";
			}

			return "error";
		}

		return "no collision";
	}

	std::string Util::checkVelocityCollision(Sprite* a, Sprite* b, float delta) {
		//std::cout << "collision between " <<
		//	a->name << "(" << a->isSolid() << ")" <<
		//	" and " <<
		//	b->name << "(" << b->isSolid() << ")" << std::endl;
		if (!a->isSolid() || !b->isSolid()) {
			//std::cout << "no collision :(" << std::endl;
			return "no collision";
		}
		//BoundingBox& abox = getAABB(a, 16);
		//BoundingBox& bbox = getAABB(b, 16);
		BoundingBox& abox = a->getBoundingBox();
		BoundingBox& bbox = b->getBoundingBox();
		//std::cout << "abox: " << abox.w << "," << abox.h << std::endl;
		//std::cout << "bbox: " << bbox.w << "," << bbox.h << std::endl;
		//std::cout << "velocityCollision delta: " << ceil(delta + 0.001) << std::endl;

		//make sure delta times don't hit 0
		float error = 0.01f;

		abox.x += ceil(a->xvel * (delta + error));
		abox.y += ceil(a->yvel * (delta + error));
		bbox.x += ceil(b->xvel * (delta + error));
		bbox.y += ceil(b->yvel * (delta + error));

		if (
			abox.x < bbox.x + bbox.w &&
			abox.x + abox.w > bbox.x &&
			abox.y < bbox.y + bbox.h &&
			abox.y + abox.h > bbox.y
		) {
			a->OnCollision(b);
			b->OnCollision(a);

			Line d1(
				(float)bbox.x, (float)bbox.y,
				(float)bbox.x + (float)bbox.w, (float)bbox.y + (float)bbox.h);
			Line d2(
				(float)bbox.x + (float)bbox.w, (float)bbox.y,
				(float)bbox.x, (float)bbox.y + (float)bbox.h);

			float cx = abox.x + (abox.w / 2.0f);
			float cy = abox.y + (abox.h / 2.0f);
			bool aboveD1 = cy < d1.solve(cx);
			bool aboveD2 = cy < d2.solve(cx);

			if (aboveD1 && aboveD2)
			{
				return "south";
			}
			else if (!aboveD1 && !aboveD2)
			{
				return "north";
			}
			else if (!aboveD1 && aboveD2)
			{
				return "east";
			}
			else if (aboveD1 && !aboveD2)
			{
				return "west";
			}

			return "error";
		}

		return "no collision";
	}

	std::vector<Sprite*> Util::GetCollisions(Sprite* s, Group* g)
	{
		std::vector<Sprite*> collisions;
		auto sprites = g->getSprites();
		for (auto& e : sprites)
		{
			if (e->getUUID() == s->getUUID())
			{
				continue;
			}

			if (checkCollision(s, e) != "no collision")
			{
				collisions.push_back(e);
			}
		}
		return collisions;
	}

	std::vector<Sprite*> Util::getVelocityCollisions(Sprite* s, Group* g, float delta) {
		std::vector<Sprite*> collisions;
		auto sprites = g->getSprites();
		for (auto& e : sprites) {
			if (e->getUUID() == s->getUUID()) {
				continue;
			}
			if (checkVelocityCollision(s, e, delta) != "no collision") {
				collisions.push_back(e);
			}
		}
		return collisions;
	}

	std::vector<Sprite*> Util::getVelocityCollisions(Sprite* sprite, std::vector<Sprite*>& vec, float delta) {
		std::vector<Sprite*> collisions;
		for (auto& e : vec) {
			if (e->getUUID() == sprite->getUUID()) {
				continue;
			}
			if (checkVelocityCollision(sprite, e, delta) != "no collision") {
				collisions.push_back(e);
			}
		}
		return collisions;
	}

	bool Util::JsonExists(nlohmann::json& o, const std::string& key)
	{
		return o.find(key) != o.end();
	}

	void Util::contain(Sprite* a, Sprite* b)
	{
		if (a == nullptr || b == nullptr)
		{
			printf("no nullptrs!\n");
		}
		if (a->x < b->x) a->x = b->x;
		else if (a->x + a->w > b->x + b->w) a->x = b->x + b->w - a->w;
		if (a->y < b->y) a->y = b->y;
		else if (a->y + a->h > b->y + b->h) a->y = b->y + b->h - a->h;
	}

	BoundingBox Util::getAABB(Sprite* a, uint32_t h)
	{
		BoundingBox aabb;
		aabb.x = floorf(roundf(a->x));
		aabb.y = floorf((roundf(a->y + a->h - h)));
		aabb.w = a->w;
		aabb.h = h;

		return aabb;
	}

	std::string Util::RectToString(SDL_Rect* r)
	{
		return "SDL_Rect [x: " + boost::lexical_cast<std::string>(r->x) +
			", y: " + boost::lexical_cast<std::string>(r->y) +
			", w: " + boost::lexical_cast<std::string>(r->w) +
			", h: " + boost::lexical_cast<std::string>(r->h) + "]";
	}

	float Util::lerp(float t, float a, float b) {
		return (1-t) * a + t * b;
	}

	void Util::formatPath(std::string& str)
	{
		int pos = str.size() - 1;
		if (str[pos] == '\\')
		{
			str[pos] = '/';
		}
		else if (str[pos] != '/')
		{
			str += '/';
		}
	}

	/*void Util::initSpdlog()
	{
		if (!isLoggerActive)
		{
			try
			{
				auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt");
				auto logger = std::make_shared<spdlog::logger>("logger", sink);
				logger->set_level(spdlog::level::debug);
				spdlog::register_logger(logger);
			}
			catch (const spdlog::spdlog_ex& ex)
			{
				std::cout << "Log init failed: " << ex.what() << std::endl;
			}
			isLoggerActive = true;
		}

	}*/
}
