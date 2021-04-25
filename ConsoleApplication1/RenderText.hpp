#pragma once
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

class Text : private SDL_Rect
{
    TTF_Font* font;
    SDL_Texture* texture;
    SDL_Color colorText;
public:
    Text();
    Text(const string fontPath, const int fontSize);
    // đặt màu cho text
    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    // xóa render text với màu background
    void free(SDL_Renderer* renderer);
    // đặt kiểu chữ nghiêng, đậm, gạch ngang...
    void setStyle(int style);
    void loadText(SDL_Renderer* renderer, string text);
    // render text ra màn hình
    void render(SDL_Renderer* renderer, int x, int y);
    int getWidth();
    int getHeight();
};