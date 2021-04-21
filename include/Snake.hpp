#pragma once

#include "Block.hpp"
#include <vector>
using namespace std;

class Snake : public vector<Block>
{
	Block* temp;
	bool isSuitable(Block newBlock);
	Direction changeDir();

	vector<SDL_Rect> src;	//get resource from assets image
public:
	bool isEatFood;
	bool alive;
	Direction nextDir;
	Snake();
	Snake(int length, vector<SDL_Rect> src);
	void paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Color grassColor[]);
	void move();
};