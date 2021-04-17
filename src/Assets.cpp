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
	enum {UP, DOWN, LEFT, RIGHT};
//set snake 
	vector<SDL_Rect> head(4), tail(4), hit(4), body(1);
head: {
	head[UP] = {0, 0, FRAME_SIZE, FRAME_SIZE};
	head[DOWN] = {FRAME_SIZE, 0, FRAME_SIZE, FRAME_SIZE};
	head[LEFT] = {2 * FRAME_SIZE, 0, FRAME_SIZE, FRAME_SIZE};
	head[RIGHT] = {3 * FRAME_SIZE, 0, FRAME_SIZE, FRAME_SIZE};
}

tail: {
	tail[UP] = {0, FRAME_SIZE, FRAME_SIZE, FRAME_SIZE};
	tail[DOWN] = {FRAME_SIZE, FRAME_SIZE, FRAME_SIZE, FRAME_SIZE};
	tail[LEFT] = {2 * FRAME_SIZE, FRAME_SIZE, FRAME_SIZE, FRAME_SIZE};
	tail[RIGHT] = {3 * FRAME_SIZE, FRAME_SIZE, FRAME_SIZE, FRAME_SIZE};
}

hit: {
	hit[UP] = {0, 2 * FRAME_SIZE, FRAME_SIZE, FRAME_SIZE};
	hit[DOWN] = {FRAME_SIZE, 2 * FRAME_SIZE, FRAME_SIZE, FRAME_SIZE};
	hit[LEFT] = {2 * FRAME_SIZE, 2 * FRAME_SIZE, FRAME_SIZE, FRAME_SIZE};
	hit[RIGHT] = {3 * FRAME_SIZE, 2 * FRAME_SIZE, FRAME_SIZE, FRAME_SIZE};
}

body: {
	body[0] = {0, 4 * FRAME_SIZE, FRAME_SIZE, FRAME_SIZE};
}

	Snake.push_back(head);
	Snake.push_back(tail);
	Snake.push_back(hit);
	Snake.push_back(body);
//free vector
	head.clear();	//head.~vector();
	tail.clear();	//tail.~vector();
	hit.clear();	//hit.~vector();
	body.clear();	//body.~vector();
//set food
	food = {FRAME_SIZE, 4 * FRAME_SIZE, FRAME_SIZE, FRAME_SIZE};
//set wall
	wall = {2 * FRAME_SIZE, 4 * FRAME_SIZE, FRAME_SIZE, FRAME_SIZE};
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