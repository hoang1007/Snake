#include "Assets.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>

Assets::Assets()
{
	texture = NULL;
}

void Assets::load(string path, SDL_Renderer* renderer)
{
	if (IMG_Init(IMG_INIT_PNG) < 0)
	{
		cerr << "Unable to init PNG " << IMG_GetError() << endl;
		return ;
	}
	// Tạo surface để load ảnh
	SDL_Surface* loadIMG = IMG_Load(path.c_str());

	if (loadIMG == NULL)
	{
		cerr << "Can't create surface to load image! " << IMG_GetError() << endl;
		return ;
	}

	// lưu kích thước của ảnh vào 2 biến w, h;
	w = loadIMG->w;
	h = loadIMG->h;

	SDL_SetColorKey(loadIMG, SDL_TRUE, SDL_MapRGB(loadIMG->format, 0, 255, 0));	// xóa màu nền thừa trong ảnh (mặc định là nền xanh)
	texture = SDL_CreateTextureFromSurface(renderer, loadIMG);

	if (texture == NULL)
	{
		cerr << "Can't create texture while load image! " << SDL_GetError() << endl;
		return ;
	}
	SDL_FreeSurface(loadIMG);	// xóa surface khi đã tạo xong texture
}

int Assets::getWidth()
{
	return w;
}

int Assets::getHeight()
{
	return h;
}
