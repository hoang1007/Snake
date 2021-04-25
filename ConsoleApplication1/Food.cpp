#include "Food.hpp"
#include "time.h"

Food::Food()
{
    srand(time(NULL));
    x = WALL_X + WALL_WIDTH / 2;
    y = WALL_Y + WALL_HEIGHT / 2;
    w = h = GRID;
}
void Food::spawn()
{
    // random x trong khoảng WALL_X + GRID <=> WALL_X + WALL_WIDTH - GRID vì ngoài khoảng đó là tường
    x = WALL_X + GRID + (rand() % ( (WALL_WIDTH - GRID) / GRID)) * GRID;

    // tương tự
    y = WALL_Y + GRID + (rand() % ( (WALL_HEIGHT - GRID) / GRID)) * GRID;
}

void Food::paint(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer, texture, &resource, this);
}
