#pragma once
#include <SDL2/SDL.h>
#include "Console.hpp"

struct Button : private SDL_Rect
{
	Button();
	Button(int _x, int _y);
	bool isPresent;
	void paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src);
	bool isClicked(int _x, int _y);
	void resize(int _w, int _h, bool center);
	void erase();
};

