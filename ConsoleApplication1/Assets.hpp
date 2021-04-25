/*
* Dùng để load tài nguyên từ file 
*/

#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
using namespace std;

class Assets
{
	int w, h;
public:
	SDL_Texture* texture;
	Assets();
	// load ảnh từ file vào texture
	void load(string path, SDL_Renderer* renderer);
	int getWidth();
	int getHeight();
};