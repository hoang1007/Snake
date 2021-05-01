#include "Food.hpp"
#include "time.h"

Food::Food()
{
    srand(time(NULL));
    x = GRID * (WALL_WIDTH / GRID + 1) / 2;
    y = GRID * (WALL_HEIGHT / GRID + 1) / 2;
    w = h = GRID;
}
void Food::spawn()
{
    // random x trong khoảng WALL_X + GRID <=> WALL_X + WALL_WIDTH - GRID vì ngoài khoảng đó là tường
    const int size_x = WALL_WIDTH / GRID - 1,
        size_y = WALL_HEIGHT / GRID - 1;
    x = WALL_X + (rand() % size_x + 1) * GRID;
    // tương tự
    y = WALL_Y + (rand() % size_y + 1) * GRID;
}

void Food::paint(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer, texture, &resource, this);
}
