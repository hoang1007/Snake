#pragma once
#include <SDL2/SDL.h>
#include "Console.hpp"

enum Direction {UP, LEFT, RIGHT, DOWN};

struct Block : public SDL_Rect
{
	Direction Dir;
	bool isCorner;
	Block();
	Block(int x, int y);
	Block(const Block& src);
	void paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src);
	/*
		paint while Block is corner
	 	code is subtraction of direction before and after change direction
	*/
	void paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, int code);
	void erase(SDL_Renderer* renderer, SDL_Color color);
	void erase(SDL_Renderer* renderer, SDL_Color color[]);
	
	bool operator == (Block _b);
};