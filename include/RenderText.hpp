#pragma once
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

class Text
{
    TTF_Font* font;
    SDL_Texture* texture;
    SDL_Color colorText;
    int w, h;
public:
    Text();
    Text(const string fontPath, const int fontSize);
    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void loadText(SDL_Renderer* renderer, string text);
    void render(SDL_Renderer* renderer, int x, int y);
    int getWidth();
    int getHeight();
};