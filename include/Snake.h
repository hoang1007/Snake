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

	vector<SDL_Rect> src;	//get resource from assets image
public:
	bool isEatFood;
	Direction preDir;
	int length;
	Snake();
	Snake(int length, vector<SDL_Rect> src);
	void paint(SDL_Renderer* renderer, SDL_Texture* texture, bool aLive, SDL_Color grassColor[]);
	bool move();
};