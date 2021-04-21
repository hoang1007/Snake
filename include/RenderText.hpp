#pragma once
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

class Text
{
    TTF_Font* font;
    SDL_Texture* texture;

public:
    Text();
    Text(const string fontPath, const int fontSize);

    void display(SDL_Renderer* renderer, string text, int x, int y, SDL_Color textColor);
};