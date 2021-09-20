#include <SDL2/SDL.h>

int SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius);

int SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius);

void SDL_RenderFillCross(SDL_Renderer *renderer, int center_x, int center_y, int radius, int thickness);
