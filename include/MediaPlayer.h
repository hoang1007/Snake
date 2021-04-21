#pragma once

#include <SDL2/SDL_mixer.h>
#include <iostream>
using namespace std;

// phat am thanh khi choi game
class Media
{
    Mix_Chunk* sound;
public:
    Media();
    Media(string path);

    /*
        phat am thanh
        loop = true: lap lai nhieu lan
        loop = false: khong lap lai
    */
    void play(bool loop);
};