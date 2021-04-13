#pragma once
#include "Block.h"

class Map
{
    Block mapPoint;
public:
    SDL_Color grassColor[2];
    Map();
    void paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src);
};