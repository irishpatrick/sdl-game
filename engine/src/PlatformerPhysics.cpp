#include "PlatformerPhysics.hpp"
#include "BoundingBox.hpp"
#include "Line.hpp"

namespace engine
{
    void PlatformerPhysics::resolveCollision(Sprite& a, Sprite& b, float delta)
    {
        BoundingBox abox = a.getBoundingBox();
        BoundingBox bbox = b.getBoundingBox();

        // next location;
        float error = 0.01f;
        abox.x += ceil(a.xvel * (delta + error));
        abox.y += ceil(a.yvel * (delta + error));
        bbox.x += ceil(b.xvel * (delta + error));
        bbox.y += ceil(b.yvel * (delta + error));

        // check for potential collision on next update
        if (
            abox.x < bbox.x + bbox.w &&
            abox.x + abox.w > bbox.x &&
            abox.y < bbox.y + bbox.h &&
            abox.y + abox.h > bbox.y)
        {
            
            // collision

            // check which face is colliding
            // calculate diagonals
            Line d1(
                (float)bbox.x, (float)bbox.y,
                (float)bbox.x + (float)bbox.w, (float)bbox.y + (float)bbox.h);
            Line d2(
                (float)bbox.x + (float)bbox.w, (float)bbox.y,
                (float)bbox.x, (float)bbox.y + (float)bbox.h);
            // centerpoint
            float cx = abox.x + (abox.w / 2.0f);
            float cy = abox.y + (abox.h / 2.0f);
            // check if center above or below each diagonal
            bool aboveD1 = cy < d1.solve(cx);
            bool aboveD2 = cy < d2.solve(cx);

            if (aboveD1 && aboveD2)
            {
                // south face
                a.collision_faces |= FACE_SOUTH;
                a.yvel = 0;
                a.y = b.y - a.h;

            }
            else if (!aboveD1 && !aboveD2)
            {
                a.collision_faces |= FACE_NORTH;
                a.yvel = 0;
                a.y = b.y + b.h;

            }
            else if (!aboveD1 && aboveD2)
            {
                a.collision_faces |= FACE_EAST;
                a.xvel = 0;
                a.x = b.x - a.w;

            }
            else if (aboveD1 && !aboveD2)
            {
                a.collision_faces |= FACE_WEST;
                a.xvel = 0;
                a.x = b.x + b.w;
            }
        }
    }
}
