#include "util.h"
#include "sprite.h"
#include "line.h"
#include "group.h"

namespace engine {

/*uint32_t Util::getNow()
{
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    );
    return ms.count();
}*/

int Util::initSDL(SDL_Window** w, SDL_Renderer** r, const std::string& title, int width, int height, bool f) {
    int result;
    if ((result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER)) < 0) {
        std::cout << "SDL_init error: " << SDL_GetError() << std::endl;
        return result;
    }

    SDL_DisplayMode current;
    if ((result = SDL_GetDesktopDisplayMode(0, &current)) < 0) {
        std::cout << "Display mode error: " << SDL_GetError() << std::endl;
        return result;
    }

    std::cout << "create window" << std::endl;

    if (f) {
        *w = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            current.w,
            current.h,
            SDL_WINDOW_SHOWN);
    } else {
        *w = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_SHOWN);
    }

    if (*w == nullptr) {
        std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        return -1;
    }

    std::cout << "create renderer" << std::endl;

    *r = SDL_CreateRenderer(
        *w,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (*r == nullptr) {
        std::cout << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (f) {
        SDL_SetWindowFullscreen(*w, SDL_WINDOW_FULLSCREEN);
        SDL_RenderSetLogicalSize(*r, current.w, current.h);
    }

    return 0;
}

SDL_Texture* Util::loadTexture(const std::string& file, SDL_Renderer* r)
{
    SDL_Texture *t = IMG_LoadTexture(r, file.c_str());
    if (t == NULL)
    {
        printf("texture error: %s\n", IMG_GetError());
    }
    return t;
}

std::string Util::checkCollision(Sprite* a, Sprite* b)
{
    if (!a->solid || !b->solid)
    {
        return "no collision";
    }
    SDL_Rect abox = getAABB(a, 16);
    SDL_Rect bbox = getAABB(b, 16);

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
    if (!a->isSolid() || !b->isSolid()) {
        return "no collision";
    }
    SDL_Rect abox = getAABB(a, 16);
    SDL_Rect bbox = getAABB(b, 16);
    abox.x += a->xvel * delta;
    abox.y += a->yvel * delta;
    bbox.x += b->xvel * delta;
    bbox.y += b->yvel * delta;

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

SDL_Rect Util::getAABB(Sprite* a, uint32_t h)
{
    SDL_Rect aabb;
    aabb.x = (int)roundf(a->x);
    aabb.y = (int)(roundf(a->y + a->h - h));
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

}
