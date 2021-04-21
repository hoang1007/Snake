#pragma once
#include <SDL2/SDL.h>
#include "Console.h"

enum class Direction {up, left, right, down, null};	//cac huong cua cac khoi (dung cho snake)

// ke thua SDL_Rect, dung nhu mot diem anh co the ve va xoa trong game 
struct Block : public SDL_Rect
{
	Direction Dir;
	bool isCorner;
	Block();
	Block(int _x, int _y);
	Block(const Block& src);
	void paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src);
	/*
		Ve len renderer khi block la goc cua ran

		code = hieu cua huong di (Direction) sau tru di truoc
	*/
	void paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, int code);
	void erase(SDL_Renderer* renderer, SDL_Color color);
	// xoa theo mau co
	void erase(SDL_Renderer* renderer, SDL_Color grassColor[]);
	//so sanh chieu rong, chieu cao, toa do cua cac Block
	bool operator == (Block _b);	
};