#include "util.h"

Util::Util()
{

}

Util::~Util()
{

}

/*uint32_t Util::getNow()
{
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    );
    return ms.count();
}*/

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
        Line d1((float)bbox.x, (float)bbox.y, (float)bbox.x + (float)bbox.w, (float)bbox.y + (float)bbox.h);
        Line d2((float)bbox.x + (float)bbox.w, (float)bbox.y, (float)bbox.x, (float)bbox.y + (float)bbox.h);

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
