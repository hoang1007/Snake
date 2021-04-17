#pragma once
#include <map>
#include <iostream>
#include "Snake.h"
#include "Assets.h"
#include "Food.h"
#include "Ground.h"
#include "RenderText.h"
#include "MediaPlayer.h"

using namespace std;
// enum sounds type
enum Type {up, down, left, right, eat1, eat2, die};
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
	void loop();
	void play();
	~Game();
};