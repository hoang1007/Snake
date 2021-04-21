#pragma once

#include "Block.h"
#include <vector>
using namespace std;

class Snake : public vector<Block>
{
	vector<Block> mark_if_change_direction;
	void change_Dir_tail();
	void mark_if_head_change();
	Block* temp;
	bool is_Suitable(Block newBlock);

	vector<SDL_Rect> src;	// luu vi tri cac phan cua snake 
public:
	bool alive;
	bool isEatFood;
	Direction preDir;
	int length;
	Snake();
	Snake(int length, vector<SDL_Rect> src);
	~Snake();
	// ve va xoa snake voi mau grass
	void paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Color grassColor[]);
	void move();
};