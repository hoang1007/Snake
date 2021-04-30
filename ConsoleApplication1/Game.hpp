#pragma once

#include <iostream>
#include "Snake.hpp"
#include "Assets.hpp"
#include "Food.hpp"
#include "Ground.hpp"
#include "RenderText.hpp"
#include "MediaPlayer.hpp"
#include "Button.hpp"

using namespace std;
// liệt kê các loại âm thanh
const int TOTAL_SOUNDS = 7;
enum SoundType {CHANGE_DIRECTION_UP, CHANGE_DIRECTION_DOWN, CHANGE_DIRECTION_LEFT, CHANGE_DIRECTION_RIGHT, SNAKE_EAT_1, SNAKE_EAT_2, SNAKE_DIE};

const int TOTALS_TEXT = 4;
enum TextRender { SCORE, HIGHEST_SCORE, PAUSE_TUTORIAL, LOSE };

class Game
{
	SDL_Window* window;

	// xử lí sự kiện bàn phím để đổi hướng và nhận lệnh dừng game, thoát game
	void pollEvent();
	// cập nhật game sau mỗi vòng lặp
	void update();

	Assets assets, pauseSprite;
	Snake snake;
	Food food;
	Ground ground;
	Text text[TOTALS_TEXT];
	Media sounds[TOTAL_SOUNDS];
	Button restartButton;

	int score;
	int highestScore;
	// lấy điểm cao nhất từ file
	int getHighestScore();
	// lưu điểm cao nhất vào file
	void saveHighestScore();
	void restart();
	void Pause();
	void unPause();
	void paint();
	// hiển thị điểm, điểm cao nhất, các hướng dẫn dừng game
	void displayInformation();
	// các hàm khởi tạo

	void textInit();
	void soundsInit();
	// đặt vị trí và kích thước cho các rect nguồn từ ảnh
	void resourceInit();
	// xóa màn hình với độ mờ cho trước (opacity)
	void clrscr(int opacity);
	const int FPS = 60;
	int frameDelay;	//độ trễ của mỗi khung hình

	bool running;
	bool isPause;
public:
	SDL_Renderer* renderer;
	
	Game();
	void loop();
	void init(); // khởi tạo 
	~Game();
};