#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
using namespace std;

class Assets
{
	
	int w, h;
public:
	vector< vector<SDL_Rect>> Snake;
	SDL_Rect food;
	SDL_Rect wall;

	SDL_Texture* texture;
	Assets();
	void set();
	void load(string path, SDL_Renderer* renderer);
};

