#include "Game.h"
#include <iostream>

using namespace std;

Game::Game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		cerr << "Game's console can't initalize!" << SDL_GetError() <<  endl;
	else
	{
		window = SDL_CreateWindow("Let's Play Fun! ^^", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		
		if (window == NULL)
			 cerr << "Can't create window" <<  endl;
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			
			if (renderer == NULL)
				 cerr << "Can't create renderer" <<  endl;
			else
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		} 
		init();
		firstRun = true;
	}
}

void Game::init()
{
	assets = Assets();
	assets.load("assets.png", renderer);
	
	int fontSize = 44;
	text = Text("font.ttf", fontSize);

	snake = Snake(5, assets.snake);

	ground = Ground();

	food = Food();

	buttonInit();

	soundsInit();

	running = true;

	isPause = false;

	score = 0;
	highestScore = getHighestScore();	//get highest score from file
}

void Game::buttonInit()
{
	int w = 400, h = 200,
	// can giua man hinh
	x = (SCREEN_WIDTH - w) / 2,
	y = SCREEN_HEIGHT / 3;

	button[HOME] = Button(x, y, w, h);
	button[QUIT] = Button(x, 2 * y, w, h);
	button[RESTART] = Button(x, y, w, h);
}

void Game::soundsInit()
{
	sounds[CHANGE_DIRECTION_UP] = Media("sounds/up.wav");

	sounds[CHANGE_DIRECTION_DOWN] = Media("sounds/down.wav");

	sounds[CHANGE_DIRECTION_LEFT] = Media("sounds/left.wav");

	sounds[CHANGE_DIRECION_RIGHT] = Media("sounds/right.wav");

	sounds[SNAKE_EAT_1] = Media("sounds/eat1.wav");

	sounds[SNAKE_EAT_2] = Media("sounds/eat2.wav");

	sounds[SNAKE_DIE] = Media("sounds/die.wav");
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}