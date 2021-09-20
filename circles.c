#include "circles.h"

// https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c
int SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    SDL_RenderDrawCircle(renderer, x, y, radius);

    while (offsety >= offsetx)
    {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0)
        {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx)
        {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety))
        {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else
        {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

void SDL_RenderFillCross(SDL_Renderer *renderer, int center_x, int center_y, int radius, int thickness)
{
    int thickness_upper_bound = (thickness * thickness) >> 2;
    for (int x = 0; x < radius; ++x)
    {
        for (int y = 0; y < radius; ++y)
        {
            int avg = (x + y) >> 1;
            int dx = x - avg;
            int dy = y - avg;
            if (dx * dx + dy * dy <= thickness_upper_bound)
            {
                SDL_RenderDrawPoint(renderer, center_x + x, center_y + y);
                SDL_RenderDrawPoint(renderer, center_x + x, center_y - y);
                SDL_RenderDrawPoint(renderer, center_x - x, center_y + y);
                SDL_RenderDrawPoint(renderer, center_x - x, center_y - y);
            }
        }
    }
}
