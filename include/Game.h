#pragma once

#include <iostream>
#include "Snake.h"
#include "Assets.h"
#include "Food.h"
#include "Ground.h"
#include "RenderText.h"
#include "MediaPlayer.h"
#include "Button.h"

using namespace std;
// liet ke cac loai sounds
const int TOTAL_SOUNDS = 7;
enum Type {CHANGE_DIRECTION_UP, CHANGE_DIRECTION_DOWN, CHANGE_DIRECTION_LEFT, CHANGE_DIRECION_RIGHT, SNAKE_EAT_1, SNAKE_EAT_2, SNAKE_DIE};

const int TOTAL_BUTTONS = 3;
enum ButtonSprite {HOME, QUIT, RESTART};

class Game
{
	SDL_Window* window;

	//xu li su kien ban phim de xac dinh huong cua snake
	void pollEvent(SDL_Event& event);
	//cap nhat game sau moi khung hinh
	void update();

	Snake snake;
	Assets assets;
	Food food;
	Ground ground;
	Text text;
	Media sounds[TOTAL_SOUNDS];
	Button button[TOTAL_BUTTONS];

	bool firstRun;
	int score;
	int highestScore;
	
	void init();
	void soundsInit();
	void buttonInit();

	// lay highest score tu file
	int getHighestScore();
	//luu highest score vao file
	void saveHighestScore();

	void Pause();
	void unPause();
	// ve len man hinh
	void paint();
	// hien thi cac thong tin nhu diem so, huong dan
	void displayInformation();
	// man hinh truoc khi vao game
	void home();

	// xoa man hinh voi do mo va mau nen mac dinh
	void clrscr(int opacity);

	void clear();
	void loop();
	
	const int FPS = 60;
	int frameDelay = 8000 / FPS; // delay cua moi khung hinh
	// trang thai cua game
	bool running;
	bool isPause;
public:
	SDL_Renderer* renderer;
	Game();
	void play();
	~Game();
};