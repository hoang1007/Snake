#include "Snake.hpp"
#include "Console.hpp"
#include <iostream>

enum {HEAD, TAIL, CRASH, BODY, CORNER};

Snake::Snake()
{
	alive = true;
	nextDir = RIGHT;
	temp = NULL;
}

Snake::Snake(int length, vector<SDL_Rect> src)
{
	if (length <= 0)
	{
		SDL_Log("Please insert avaible length\n");
		return;
	}

	alive = true;
	nextDir = RIGHT;
	this->src = src;

	for (int i = 0; i < length; i++)
	{
		Block newBlock(WALL_WIDTH / 2 - i * GRID, WALL_HEIGHT / 2);
		push_back(newBlock);
	}
	temp = NULL;
}

void Snake::paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Color grassColor[])
{
	for (int i = 1; i < size() - 1; i++)
	{
		if (at(i).isCorner)
		{
			at(i).erase(renderer, grassColor);
			at(i).paint(renderer, texture, src[CORNER], at(i + 1).Dir - at(i).Dir);
		}
		else 
			at(i).paint(renderer, texture, src[BODY]);
	}

	if (temp != NULL)
		temp->erase(renderer, grassColor);

	back().erase(renderer, grassColor);
	back().paint(renderer, texture, src[TAIL]);

	if (alive)	
		front().paint(renderer, texture, src[HEAD]);
	else
		front().paint(renderer, texture, src[CRASH]);
}

Direction Snake::changeDir()
{
	if (front().Dir + nextDir != 3 && front().Dir != nextDir)
	{
		front().isCorner = true;
		return nextDir;
	}
	return front().Dir;
}

void Snake::move()
{
	front().Dir = changeDir();

	Block newBlock(front());

	switch (front().Dir)
	{
	case RIGHT:
		newBlock.x += GRID;
		break;
	case LEFT:
		newBlock.x -= GRID;
		break;
	case DOWN:
		newBlock.y += GRID;
		break;
	case UP:
		newBlock.y -= GRID;
		break;
	default:
		break;
	}
	
	if (isSuitable(newBlock))
		insert(begin(), newBlock);
	else alive = false;

	temp = new Block(back());

	if (isEatFood)
		isEatFood = false;
	else pop_back();
}

bool Snake::isSuitable(Block newBlock)
{
	for (int i = 0; i < size(); i++)
		if (newBlock == at(i)) return false;
	
	if (newBlock.x <= WALL_X || newBlock.x >= WALL_WIDTH + WALL_X || 
			newBlock.y <= WALL_X || newBlock.y >= WALL_Y + WALL_HEIGHT)
		return false;
	return true;
}