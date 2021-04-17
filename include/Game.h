#pragma once
#include <SDL2/SDL.h>
#include "Snake.h"
#include "Assets.h"
#include "Food.h"
#include "Map.h"
#include "RenderText.h"
#include "MediaPlayer.h"

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
	vector<Media> sounds;

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