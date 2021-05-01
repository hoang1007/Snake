#include "Snake.hpp"
#include "Console.hpp"
#include <iostream>

Snake::Snake()
{
	alive = true;
	nextDir = RIGHT;
	temp = NULL;
}

Snake::Snake(int length)
{
	if (length <= 0)
	{
		SDL_Log("Please insert avaible length\n");
		return;
	}

	alive = true;
	nextDir = RIGHT;
	src.resize(TOTALS_PARTS);
	int mid = (WALL_WIDTH / 2) * GRID;
	for (int i = 0; i < length; i++)
	{
		Block newBlock( WALL_X + GRID + i * GRID, WALL_Y + GRID);
		push(newBlock);
	}
	temp = NULL;
	cerr << front().x << " " << front().y << endl;
}

void Snake::paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Color grassColor[])
{
	// vẽ thân của rắn
	ReverseQueue<Block>::iterator iter, prev_iter = end();

	for (iter = secondlast(); iter != begin(); iter--, prev_iter--)
	{
		if (iter->isCorner)
		{
			iter->erase(renderer, grassColor);
			iter->paint(renderer, texture, src[CORNER], prev_iter->Dir - iter->Dir);
		}
		else iter->paint(renderer, texture, src[BODY]);
	}

	// xóa phần thừa ở đuôi của rắn
	if (temp != NULL)
		temp->erase(renderer, grassColor);

	back().erase(renderer, grassColor);
	back().paint(renderer, texture, src[TAIL]);

	//front().erase(renderer, grassColor);
	if (alive)
		front().paint(renderer, texture, src[HEAD]);
	else
		front().paint(renderer, texture, src[CRASH]);
}

Direction Snake::changeDir()
{
	// Không được đi hướng ngược lại với hiện tại của rắn
	if (front().Dir + nextDir != 3 && front().Dir != nextDir)	// vì LEFT + RIGHT = UP + DOWN = 3 (từ enum Direction)
	{
		front().isCorner = true;	//sau khi đổi hướng thì đầu là góc của rắn
		return nextDir;
	}
	return front().Dir;
}

void Snake::move()
{
	front().Dir = changeDir();	// cập nhật hướng mới
	
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
		push(newBlock);
	else alive = false;	// nếu không hợp lệ thì rắn chết

	if (isEatFood)	// nếu ăn thức ăn thì không xóa Block đuôi của rắn => chiều dài tăng lên 1
		isEatFood = false;
	else temp = new Block(pop());	// lưu lại phần đuôi sau khi bị xóa
}

bool Snake::isSuitable(Block newBlock)
{
	if (find(newBlock)) return false;
	
	if (newBlock.x <= WALL_X || newBlock.x >= WALL_WIDTH + WALL_X || 
			newBlock.y <= WALL_X || newBlock.y >= WALL_Y + WALL_HEIGHT)
		return false;
	return true;
}

Snake::~Snake()
{
	cerr << "Snake destructor called!" << endl;
	src.clear();
	delete temp;
	clear();
}