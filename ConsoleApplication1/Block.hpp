/*
* Dùng như một ô màu trong game
* Dùng để tạo các vật thể như rắn, thức ăn, các ô của bản đồ
*/

#pragma once
#include <SDL2/SDL.h>
#include "Console.hpp"

enum Direction { UP, LEFT, RIGHT, DOWN };	// liệt kê các hướng di chuyển

struct Block : public SDL_Rect
{
	Direction Dir;
	bool isCorner;	// xem khối này có phải là góc của rắn hay không 
	Block();
	Block(int x, int y);	// hàm khởi tạo với tọa độ cho trước
	Block(const Block& src);	// hàm khởi tạo copy

	// Hàm vẽ mặc định
	void paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src);
	/*
	* Hàm vẽ khi Block là góc của rắn
	* code = hiệu của hướng trước đó trừ đi hướng hiện tại, từ đó tính được góc để render ảnh
	*/
	void paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, int code);

	// Hàm tô block với màu cho trước
	void erase(SDL_Renderer* renderer, SDL_Color color);
	/*
	* Hàm tô Block với nhiều màu
	*/
	void erase(SDL_Renderer* renderer, SDL_Color color[]);
	// toán tử so sánh tọa độ, kích thước của các Block
	bool operator == (Block _b);

	// đặt tọa độ của block 
	void setCoordinate(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};