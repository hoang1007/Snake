#include "MediaPlayer.h"

Media::Media()
{
    sound = NULL;
}

Media::Media(string path)
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        cerr << Mix_GetError << endl;
    else
    {
        sound = Mix_LoadWAV(path.c_str());
        if (sound == NULL)
            cerr << "Can't open sound! " << Mix_GetError << endl;
    }
}

void Media::play(bool loop)
{
    Mix_PlayChannel(-1, sound, loop);
}