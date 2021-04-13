#include "RenderText.h"
#include "Console.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Text::Text()
{
    font = NULL;
    texture = NULL;
}

Text::Text(const string fontPath, const int fontSize)
{
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        cerr << "SDL_image couldn't initialize! " << IMG_GetError() << endl;
    if (TTF_Init() == -1)
        cerr << "SDL_TTF couldn't initialize! " << TTF_GetError() << endl;

    font = TTF_OpenFont(fontPath.c_str(), fontSize);

    if (font == NULL)
        cerr << "Faild to load font! " << TTF_GetError() << endl;
}

void Text::display(SDL_Renderer* renderer, string text, SDL_Color textColor, SDL_Rect dst)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

    if (textSurface == NULL)
        cerr << "Unable to render text surface! " << TTF_GetError() << endl;
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);

        if (texture == NULL)
            cerr << "Unable to create texture from render text! " << TTF_GetError() << endl;
        
        //get rid of old render text
        SDL_SetRenderDrawColor(renderer, R_BACKGROUND, G_BACKGROUND, B_BACKGROUND, 255);
        SDL_RenderFillRect(renderer, &dst);

        dst.w = textSurface->w;
        dst.h = textSurface->h;

        SDL_RenderCopy(renderer, texture, NULL, &dst);
    }
    SDL_FreeSurface(textSurface);
}