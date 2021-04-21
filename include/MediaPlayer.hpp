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

    void play(bool loop);
};