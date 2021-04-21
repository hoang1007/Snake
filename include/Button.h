#pragma once

#include "Block.h"
#include <string>

using namespace std;

// ke thua SDL_Rect, dung de tao cac nut bam trong game
class Button : public SDL_Rect
{
    SDL_Texture* texture;
    bool isPresent;
public:
    Button();
    // khoi tao button co kich thuoc san
    Button(int x, int y, int w, int h);
    // khoi tao button tu file nguon
    Button(SDL_Renderer* renderer ,const string path);

    // ve button da duoc load tu file nguon
    void paint(SDL_Renderer* renderer);

    // ve button khong duoc load tu file nguon
    void paint(SDL_Renderer* renderer, SDL_Color color);

    void erase();
    
    // xac nhan xem button co duoc nhan hay khong
    bool isClicked(int& _x, int& _y);
};