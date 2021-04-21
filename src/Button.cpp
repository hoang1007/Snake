#include "Button.h"
#include "SDL2/SDL_image.h"
#include <iostream>

Button::Button()
{
    texture = NULL;
    x = y = w = h = 0;
}

Button::Button(int x, int y, int w, int h)
{
    texture = NULL;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Button::Button(SDL_Renderer* renderer ,const string path)
{
    if (IMG_Init(IMG_INIT_PNG) < 0)
        cerr << "Unable to initialize IMG " << IMG_GetError << endl;

    SDL_Surface* load = IMG_Load(path.c_str());

    if (load == NULL)
    {
        cerr << "Can't load image " << IMG_GetError << endl;
        return ;
    }

    SDL_SetColorKey(load, SDL_TRUE, SDL_MapRGB(load->format, 0, 255, 0));
    texture = SDL_CreateTextureFromSurface(renderer, load);

    if (texture == NULL)
    {
        cerr << "Can't create texture " << IMG_GetError << endl;
        return ;
    }
}

void Button::erase()
{
    isPresent = false;
}

void Button::paint(SDL_Renderer* renderer, SDL_Color color)
{
    isPresent = true;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, this);
}

void Button::paint(SDL_Renderer* renderer)
{
    isPresent = true;
    SDL_RenderCopy(renderer, texture, NULL, this);
}



bool Button::isClicked(int& _x, int& _y)
{
    if (!isPresent) return false;

    if (w == 0 || h == 0) return false;

    if (_x < x || _y < y) return false;

    if (_x > x + w || _y > h + y)
        return false;
    return true;
}