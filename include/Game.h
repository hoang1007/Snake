#pragma once
#include <SDL2/SDL.h>
#include "Snake.h"
#include "Assets.h"
#include "Food.h"
#include "Map.h"
#include "RenderText.h"

class Game
{
	SDL_Window* window;

	void pollEvent(SDL_Event& event);
	void update();

	Snake snake;
	Assets assets;
	Food food;
	Map map;
	Text text;
	
	int score;
	int highestScore;
	int getHighestScore();
	void saveHighestScore();
	void Pause();
	void unPause();
	void paint();
	void displayInformation();

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