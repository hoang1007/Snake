#include "Assets.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Assets::Assets()
{
	texture = NULL;
}

void Assets::set()
{
	int FRAME_SIZE = w / 4;

//set snake
	enum {HEAD, TAIL, CRASH, BODY, CORNER};
	SDL_Rect head = {0, 0, FRAME_SIZE, FRAME_SIZE},
			tail = {FRAME_SIZE, 0, FRAME_SIZE, FRAME_SIZE},
			crash = {2 * FRAME_SIZE, 0, FRAME_SIZE, FRAME_SIZE},
			body = {3 * FRAME_SIZE, 0, FRAME_SIZE, FRAME_SIZE},
			corner = {0, FRAME_SIZE, FRAME_SIZE, FRAME_SIZE};
		
	snake.push_back(head);
	snake.push_back(tail);
	snake.push_back(crash);
	snake.push_back(body);
	snake.push_back(corner);
	
//set food
	food = {FRAME_SIZE, FRAME_SIZE, FRAME_SIZE, FRAME_SIZE};
//set wall
	wall = {2 * FRAME_SIZE, FRAME_SIZE, FRAME_SIZE, FRAME_SIZE};
}

void Assets::load(string path, SDL_Renderer* renderer)
{
	if (IMG_Init(IMG_INIT_PNG) < 0)
	{
		cerr << "Unable to init PNG " << IMG_GetError() << endl;
		return ;
	}
	SDL_Surface* loadIMG = IMG_Load(path.c_str());

	if (loadIMG == NULL)
	{
		cerr << "Can't create surface to load image! " << IMG_GetError() << endl;
		return ;
	}

	w = loadIMG->w;
	h = loadIMG->h;

	SDL_SetColorKey(loadIMG, SDL_TRUE, SDL_MapRGB(loadIMG->format, 0, 255, 0));
	texture = SDL_CreateTextureFromSurface(renderer, loadIMG);

	if (texture == NULL)
	{
		cerr << "Can't create texture while load image! " << SDL_GetError() << endl;
		return ;
	}
	SDL_FreeSurface(loadIMG);

	//set img resource
	set();
}