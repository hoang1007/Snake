#include "Block.h"

Block::Block()
{
	Dir = Direction::right;
	x = WALL_WIDTH / 2;
	y = WALL_HEIGHT / 2;
	w = h = GRID;
}

Block::Block(int x, int y)
{
	Dir = Direction::right;
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
}

void Block::paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src)
{
	double angle = 0;
	switch (Dir)
	{
	case Direction::up:
		angle = -90;
		break;
	case Direction::down:
		angle = 90;
		break;
	case Direction::right:
		angle = 0;
		break;
	case Direction::left:
		angle = 180;
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
	if ((this->x + this->y) / GRID % 2)
		erase(renderer, color[0]);
	else erase(renderer, color[1]);
}

bool Block::operator==(Block _b)
{
	if (this->x == _b.x && this->y == _b.y && this->w == _b.w && this->h == _b.h)
		return true;
	return false;
}