#include "RenderText.hpp"
#include "Console.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>

Text::Text()
{
    font = NULL;
    texture = NULL;
    colorText = {255, 255, 255, 255};   // mặc định màu text là màu trắng
    x = y = w = h = 0;
}

Text::Text(const string fontPath, const int fontSize)
{
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        cerr << "SDL_image couldn't initialize! " << IMG_GetError << endl;
    if (TTF_Init() == -1)
        cerr << "SDL_TTF couldn't initialize! " << TTF_GetError << endl;

    font = TTF_OpenFont(fontPath.c_str(), fontSize);

    if (font == NULL)
        cerr << "Faild to load font! " << TTF_GetError << endl;
    colorText = {255, 255, 255, 255};   // màu mặc định là màu trắng
    w = h = 0;
}

void Text::free(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, R_BACKGROUND, G_BACKGROUND, B_BACKGROUND, 255);
    SDL_RenderFillRect(renderer, this);
}

void Text::setStyle(int style)
{
    TTF_SetFontStyle(font, style);
}

void Text::loadText(SDL_Renderer* renderer, string text)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), colorText);

    if (textSurface == NULL)
        cerr << "Unable to render text surface! " << TTF_GetError << endl;
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);

        if (texture == NULL)
            cerr << "Unable to create texture from render text! " << TTF_GetError << endl;
        else
        {
            w = textSurface->w;
            h = textSurface->h;
        }
    }
    SDL_FreeSurface(textSurface);
}

void Text::render(SDL_Renderer* renderer, int x, int y)
{
    this->x = x;
    this->y = y;
    SDL_RenderCopy(renderer, texture, NULL, this);
}

void Text::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    colorText = {r, g, b, a};
}

int Text::getHeight()
{
    return h;
}

int Text::getWidth()
{
    return w;
}