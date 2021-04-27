#pragma once
#include "Block.hpp"
#include "Console.hpp"

struct Button : private SDL_Rect
{
	Button();
	Button(int _x, int _y);
	SDL_Rect resource;	// lưu vị trí, kích thước button trong file nguồn 
	bool isPresent;	// nút đã hiển thị trên màn hình hay không
	// vẽ ra màn hình
	void paint(SDL_Renderer* renderer, SDL_Texture* texture);
	/* 
	* xem button có được nhấn hay không 
	* Trả về true nếu được nhấn 
	* Trả về false nếu không nhấn 
	*/
	bool isClicked(int _x, int _y);
	// đặt lại tọa độ cho button
	void setCoordinate(int _x, int _y);
	/*
	* Đặt lại kích thước với tùy chọn center
	* center = true : căn giữa
	* center = false : không căn giữa 
	*/
	void resize(int _w, int _h, bool center);
	// đặt lại biến hiển thị (isPresent) bằng false 
	void erase();
	// trả về chiều rộng của button 
	int getWidth();
	// trả về chiều cao của button 
	int getHeight();
};

