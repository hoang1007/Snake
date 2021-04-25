#pragma once

#include <SDL2/SDL_mixer.h>
#include <iostream>
using namespace std;

class Media
{
    Mix_Chunk* sound;
public:
    Media();
    Media(string path);

    /*
    * phát âm thanh 
    * loop = true : phát lại liên tục
    * loop = false : chỉ phát một lần
    */
    void play(bool loop);
};