#include "Ground.h"

Ground::Ground()
{
    point = Block();
    grassColor[0] = {102, 204, 0, 255};
    grassColor[1] = {76, 153, 0, 100};
}

void Ground::paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src)
{
    for (int i = WALL_X; i <= WALL_WIDTH + WALL_X; i += GRID)
    {
        for (int j = WALL_Y; j <= WALL_HEIGHT + WALL_Y; j += GRID)
        {
            point.x = i;     point.y = j;

            //neu la tuong
            if (i == WALL_X || i == WALL_WIDTH + WALL_X || j == WALL_Y || j == WALL_Y + WALL_HEIGHT)
                point.paint(renderer, texture, src);
            else
                    point.erase(renderer, (i + j) / GRID % 2 ? grassColor[0] : grassColor[1]);
        }
    }
}