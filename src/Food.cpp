#include "Food.h"
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
    /*
        random x, y trong khoang tu WALL_X + GRID den WALL_X + WALL_WIDTH 
        vi WALL_X va WALL_X + WALL_WIDTH la tuong
    */
    x = WALL_X + GRID + (rand() % ( (WALL_WIDTH - GRID) / GRID)) * GRID;

    y = WALL_Y + GRID + (rand() % ( (WALL_HEIGHT - GRID) / GRID)) * GRID;
}