#include "Snake.h"
#include "Console.h"
#include <iostream>

enum {HEAD, TAIL, CRASH, BODY, CORNER};

Snake::Snake()
{
	length = 0;
	preDir = Direction::null;
}

Snake::Snake(int length, vector<SDL_Rect> src)
{
	if (length <= 0)
	{
		SDL_Log("Please insert avaible length\n");
		return;
	}
	
	this->length = length;
	preDir = Direction::right;
	this->src = src;
	for (int i = 0; i < this->length; i++)
	{
		Block newBlock(WALL_WIDTH / 2 - i * GRID, WALL_HEIGHT / 2);
		push_back(newBlock);
	}
	temp = NULL;
}

void Snake::paint(SDL_Renderer* renderer, SDL_Texture* texture, bool aLive, SDL_Color grassColor[])
{
	for (int i = 1; i < size() - 1; i++)
	{
		if (at(i).isCorner)
		{
			at(i).erase(renderer, grassColor);
			at(i).paint(renderer, texture, src[CORNER], (int) at(i + 1).Dir - (int) at(i).Dir);
		}
		else 
			at(i).paint(renderer, texture, src[BODY]);
	}

	if (temp != NULL)
		temp->erase(renderer, grassColor);
	back().erase(renderer, grassColor);

	int tailDir = (int) back().Dir;
	back().paint(renderer, texture, src[TAIL]);

	int headDir = (int) front().Dir;
	if (aLive)	
		front().paint(renderer, texture, src[HEAD]);
	else
		front().paint(renderer, texture, src[CRASH]);
}


bool Snake::move()
{
	Block newBlock(front());

	mark_if_head_change();
	change_Dir_tail();

	switch (front().Dir)
	{
	case Direction::right:
		newBlock.x += GRID;
		break;
	case Direction::left:
		newBlock.x -= GRID;
		break;
	case Direction::down:
		newBlock.y += GRID;
		break;
	case Direction::up:
		newBlock.y -= GRID;
		break;
	default:
		break;
	}
	
	if (is_Suitable(newBlock))
		insert(begin(), newBlock);
	else return false;

	temp = new Block(back());
	if (!isEatFood)
		pop_back();
	else isEatFood = false;

	return true;
}

void Snake::change_Dir_tail()
{
	if (mark_if_change_direction.empty())
		return ;
	if (back() == mark_if_change_direction.front())
	{
		back().Dir = mark_if_change_direction.front().Dir;
		mark_if_change_direction.erase(mark_if_change_direction.begin());
	}
}
void Snake::mark_if_head_change()
{
	if (front().Dir != preDir)
	{
		front().isCorner = true;
		preDir = front().Dir;
		mark_if_change_direction.push_back(front());
	}
}
bool Snake::is_Suitable(Block newBlock)
{
	for (int i = 0; i < size(); i++)
		if (newBlock == at(i)) return false;
	
	if (newBlock.x <= WALL_X || newBlock.x >= WALL_WIDTH + WALL_X || 
			newBlock.y <= WALL_X || newBlock.y >= WALL_Y + WALL_HEIGHT)
		return false;
	return true;
}