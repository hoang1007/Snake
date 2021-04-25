#pragma once
#include "Block.hpp"

class Ground
{
    Block point;    // điểm chạy để tô màu cho bản đồ
public:
    SDL_Color grassColor[2];
    SDL_Rect rockSrc;   // lưu lại vị trí và kích thước của đá trong file nguồn
    Ground();
    void paint(SDL_Renderer* renderer, SDL_Texture* texture);
};