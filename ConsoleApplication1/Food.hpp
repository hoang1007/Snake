#pragma once
#include "Block.hpp"

struct Food : public Block
{
    SDL_Rect resource;  // lưu tọa độ và kích thước trong ảnh nguồn
    Food();
    // hàm random tọa độ thức ăn
    void spawn();
    void paint(SDL_Renderer* renderer, SDL_Texture* texture);
};