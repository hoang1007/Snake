#include "Block.hpp"

Block::Block()
{
	Dir = RIGHT;
	isCorner = false;
	x = WALL_WIDTH / 2;
	y = WALL_HEIGHT / 2;
	w = h = GRID;
}

Block::Block(int x, int y)
{
	Dir = RIGHT;
	isCorner = false;
	this->x = x;
	this->y = y;
	this->w = this->h = GRID;
}

Block::Block(const Block& src)
{
	x = src.x;
	y = src.y;
	w = src.w;
	h = src.h;
	Dir = src.Dir;
	isCorner = false;
}

void Block::paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src)
{
	double angle = 0;
	switch (Dir)
	{
	case UP:
		angle = -90;
		break;
	case DOWN:
		angle = 90;
		break;
	case RIGHT:
		angle = 0;
		break;
	case LEFT:
		angle = 180;
		break;
	default:
		break;
	}

	SDL_RenderCopyEx(renderer, texture, &src, this, angle, NULL, SDL_FLIP_NONE);
}

void Block::paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, int code)
{
	double angle = 0;
	switch (code)
	{
	case 2:
		angle = 0;
		break;
	case -2:
		angle = 180;
		break;
	case -1:
		angle = -90;
		break;
	case 1:
		angle = 90;
		break;
	default:
		break;
	}

	SDL_RenderCopyEx(renderer, texture, &src, this, angle, NULL, SDL_FLIP_NONE);
}

void Block::erase(SDL_Renderer* renderer, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, this);
}

void Block::erase(SDL_Renderer* renderer, SDL_Color color[])
{
	if ((x + y) / GRID % 2)
		erase(renderer, color[0]);
	else erase(renderer, color[1]);
}

bool Block::operator==(Block _b)
{
	if (this->x == _b.x && this->y == _b.y && this->w == _b.w && this->h == _b.h)
		return true;
	return false;
}