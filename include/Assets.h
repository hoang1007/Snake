#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
using namespace std;

// Load tai nguyen tu anh co san
class Assets
{
	int w, h;	// chieu rong va chieu cao cua anh duoc load
public:
	vector<SDL_Rect> snake;	// luu vi tri cua snake trong anh duoc load
	SDL_Rect food;	// luu vi tri cua food trong anh
	SDL_Rect rock;	// luu vi tri cua da trong anh

	SDL_Texture* texture;
	Assets();
	// dat vi tri cho cac doi tuong
	void set();
	// load anh vao renderer tu texture
	void load(string path, SDL_Renderer* renderer);
};