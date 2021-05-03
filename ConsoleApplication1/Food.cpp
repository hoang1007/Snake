#include "Food.hpp"
#include "time.h"

Food::Food()
{
    srand(time(NULL));
    x = GRID * (WALL_WIDTH / GRID + 1) / 2;
    y = GRID * (WALL_HEIGHT / GRID + 1) / 2;
    w = h = GRID;
}

void Food::paint(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer, texture, &resource, this);
}
