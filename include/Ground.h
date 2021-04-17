#pragma once
#include "Block.h"

class Ground
{
    Block point;
public:
    SDL_Color grassColor[2];
    Ground();
    void paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src);
};