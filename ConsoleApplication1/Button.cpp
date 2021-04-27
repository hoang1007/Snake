#include "Button.hpp"

Button::Button()
{
	x = y = 0;
	w = h = GRID;
	isPresent = false;
	resource = { 0, 0, 0, 0 };
}

Button::Button(int _x, int _y)
{
	x = _x;
	y = _y;
	w = h = GRID;
	isPresent = false;
	resource = { 0, 0, 0, 0 };
}

void Button::paint(SDL_Renderer* renderer, SDL_Texture* texture)
{
	isPresent = true;
	SDL_RenderCopy(renderer, texture, &resource, this);
}

bool Button::isClicked(int _x, int _y)
{
	if (!isPresent) return false;
	if (_x < x || _y < y) return false;
	if (_x > x + w || _y > y + h) return false;
	return true;
}

void Button::setCoordinate(int _x, int _y)
{
	x = _x;
	y = _y;
}

void Button::resize(int _w, int _h, bool center)
{
	if (center)
	{
		int delta_w = _w - w,
			delta_h = _h - h;
		x -= delta_w / 2;
		y += delta_h / 2;
	}
	w = _w;
	h = _h;
}

void Button::erase()
{
	isPresent = false;
}

int Button::getWidth()
{
	return w;
}

int Button::getHeight()
{
	return h;
}
