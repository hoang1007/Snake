#pragma once
#include <map>
#include <iostream>
#include "Snake.h"
#include "Assets.h"
#include "Food.h"
#include "Ground.h"
#include "RenderText.h"
#include "MediaPlayer.h"
#include "Button.h"

using namespace std;
// enum sounds type
enum class Type {up, down, left, right, eat1, eat2, die};
const int TOTAL_BUTTONS = 3;

enum ButtonSprite {HOME, QUIT, RESTART};

class Game
{
	SDL_Window* window;

	void pollEvent(SDL_Event& event);
	void update();

	Snake snake;
	Assets assets;
	Food food;
	Ground ground;
	Text text;
	map<Type, Media> sounds;
	Button button[TOTAL_BUTTONS];

	bool firstRun;
	int score;
	int highestScore;
	void init();
	int getHighestScore();
	void saveHighestScore();
	void Pause();
	void unPause();
	void paint();
	void displayInformation();
	void soundsInit();
	void buttonInit();

	// clear screen with opacity
	void clrscr(int opacity);

	void clear();
	void loop();
	
	const int FPS = 60;
	int frameDelay = 8000 / FPS;
	bool running;
	bool isPause;
public:
	SDL_Renderer* renderer;

	Game();
	void play();
	~Game();
};