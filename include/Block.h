#pragma once
#include <SDL2/SDL.h>
#include "Console.h"

enum class Direction {up, down, left, right, null};

struct Block : public SDL_Rect
{
	Direction Dir;
	Block();
	Block(int x, int y);
	Block(const Block& src);
	void paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src);
	void erase(SDL_Renderer* renderer, SDL_Color color);
	void erase(SDL_Renderer* renderer, SDL_Color color[]);
	
	bool operator == (Block _b);
};