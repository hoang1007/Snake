#pragma once
#include <map>
#include <iostream>
#include "Snake.hpp"
#include "Assets.hpp"
#include "Food.hpp"
#include "Ground.hpp"
#include "RenderText.hpp"
#include "MediaPlayer.hpp"

using namespace std;
// enum sounds type
const int TOTAL_SOUNDS = 7;
enum SoundType {CHANGE_DIRECTION_UP, CHANGE_DIRECTION_DOWN, CHANGE_DIRECTION_LEFT, CHANGE_DIRECTION_RIGHT, SNAKE_EAT_1, SNAKE_EAT_2, SNAKE_DIE};

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
	Media sounds[TOTAL_SOUNDS];

	int score;
	int highestScore;
	int getHighestScore();
	void saveHighestScore();
	void Pause();
	void unPause();
	void paint();
	void displayInformation();
	void soundsInit();
	
	const int FPS = 60;
	int frameDelay = 8000 / FPS;
	bool running;
	bool isPause;
public:
	SDL_Renderer* renderer;

	Game();
	void init();
	void loop();
	void play();
	~Game();
};