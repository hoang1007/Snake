#include "Game.hpp"
#include "Console.hpp"

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
		}
		//init stat 

		assets = Assets();
		assets.load("assets.png", renderer);
		
		int fontSize = 44;
		text = Text("font.ttf", fontSize);

		snake = Snake(5, assets.snake);

		ground = Ground();

		food = Food();

		soundsInit();

		running = true;
		isPause = false;

		score = 0;
		highestScore = getHighestScore();	//get highest score from file
	}
}

void Game::soundsInit()
{
	sounds[CHANGE_DIRECTION_UP] = Media("sounds/up.wav");

	sounds[CHANGE_DIRECTION_DOWN] = Media("sounds/down.wav");

	sounds[CHANGE_DIRECTION_LEFT] = Media("sounds/left.wav");

	sounds[CHANGE_DIRECTION_RIGHT] = Media("sounds/right.wav");

	sounds[SNAKE_EAT_1] = Media("sounds/eat1.wav");

	sounds[SNAKE_EAT_2] = Media("sounds/eat2.wav");

	sounds[SNAKE_DIE] = Media("sounds/die.wav");
}

void Game::paint()
{
	// clear old render
	SDL_SetRenderDrawColor(renderer, R_BACKGROUND, G_BACKGROUND, B_BACKGROUND, 255);
	SDL_RenderClear(renderer);

	//present snake, food and ground
	ground.paint(renderer, assets.texture, assets.wall);
	snake.paint(renderer, assets.texture, ground.grassColor);
	food.paint(renderer, assets.texture, assets.food);
	displayInformation();

	SDL_RenderPresent(renderer);
}