#pragma once

#include "Block.h"
#include <string>

using namespace std;

class Button : public SDL_Rect
{
    SDL_Texture* texture;
    bool isPresent;
public:
    Button();
    Button(int x, int y, int w, int h);
    Button(SDL_Renderer* renderer ,const string path);

    // present while Button is loaded from file
    void present(SDL_Renderer* renderer);

    //present while Button isn't loaded from file
    void present(SDL_Renderer* renderer, SDL_Color color);

    void erase();
    
    bool isClicked(int& _x, int& _y);
};