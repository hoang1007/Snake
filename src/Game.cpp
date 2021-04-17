#include "Game.h"
#include "Console.h"
#include <iostream>
#include <fstream>
#include <string>

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
		}
		//init stat 

		assets = Assets();
		assets.load("game.png", renderer);
		
		int fontSize = 44;
		text = Text("font.ttf", fontSize);

		snake = Snake(4, assets.Snake);

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
	sounds[Type::up] = Media("sounds/up.wav");

	sounds[Type::down] = Media("sounds/down.wav");

	sounds[Type::left] = Media("sounds/left.wav");

	sounds[Type::right] = Media("sounds/right.wav");

	sounds[Type::eat1] = Media("sounds/eat1.wav");

	sounds[Type::eat2] = Media("sounds/eat2.wav");

	sounds[Type::die] = Media("sounds/die.wav");
}

void Game::paint()
{
	// clear old render
	SDL_SetRenderDrawColor(renderer, R_BACKGROUND, G_BACKGROUND, B_BACKGROUND, 255);
	SDL_RenderClear(renderer);

	//present snake, food and ground
	ground.paint(renderer, assets.texture, assets.wall);
	snake.paint(renderer, assets.texture, running, ground.grassColor);
	food.paint(renderer, assets.texture, assets.food);
	displayInformation();

	SDL_RenderPresent(renderer);
}

void Game::pollEvent(SDL_Event& event)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_w:
	case SDLK_UP:
		if (snake.preDir != Direction::down && !isPause)
		{
			snake.front().Dir = Direction::up;
			sounds[Type::up].play(false);
		}
		break;
	case SDLK_s:
	case SDLK_DOWN:
		if (snake.preDir != Direction::up && !isPause)
		{
			snake.front().Dir = Direction::down;
			sounds[Type::down].play(false);
		}
		break;
	case SDLK_a:
	case SDLK_LEFT:
		if (snake.preDir != Direction::right && !isPause)
		{
			snake.front().Dir = Direction::left;
			sounds[Type::left].play(false);
		}
		break;
	case SDLK_d:
	case SDLK_RIGHT:
		if (snake.preDir != Direction::left && !isPause)
		{
			snake.front().Dir = Direction::right;
			sounds[Type::right].play(false);
		}
		break;
	case SDLK_p:
	case SDLK_SPACE:
		isPause ? unPause() : Pause();
		break;
	default:
		break;
	}
}

int Game::getHighestScore()
{
	fstream f("highestScore");
	int res = 0;
	if (f.fail())
		cerr << "Unable to open file to get highest score!";
	else
		f >> res;
	f.close();
	return res;
}

void Game::saveHighestScore()
{
	if (highestScore < score)
	{
		fstream f("highestScore");
		if (f.fail())
			cerr << "Unable to open file to save highest score!";
		else
			f << score;
	}
}

void Game::displayInformation()
{
	// display score
	const SDL_Color scoreColor = {255, 31, 31, 255},
					highestScoreColor = {51, 25, 0, 255};
	//set width and height enough to erase old render text
	int score_x = WALL_WIDTH + WALL_X + GRID,
		score_y = WALL_Y + GRID;
	text.display(renderer, "SCORE: " + to_string(score), score_x, score_y, scoreColor);

	int highestScore_x = score_x,
		highestScore_y = score_y + 2 * GRID;
	text.display(renderer, "Highest Score: " + to_string(highestScore), highestScore_x, highestScore_y, highestScoreColor);


	//display pause game tutorial
	SDL_Color pauseColor = {255, 255, 51};
	
	int x = WALL_X + GRID + WALL_WIDTH;
	int y = SCREEN_HEIGHT / 2;

	text.display(renderer, "press p to pause!", x, y, pauseColor);
}

void Game::Pause()
{
	isPause = true;
	//delay when open menu
	SDL_Delay(100);
	SDL_Rect p = {0, 0, 500, 500};
	SDL_SetRenderDrawColor(renderer, R_BACKGROUND, G_BACKGROUND, B_BACKGROUND, 255);
	SDL_RenderFillRect(renderer, &p);
	SDL_RenderPresent(renderer);
}

void Game::unPause()
{
	SDL_Delay(100);
	isPause = false;

	paint();
}

void Game::update()
{
	if (snake.move() == false)
	{
		running = false;
		sounds[die].play(false);
	}

	if (food == snake.front())
	{
		snake.isEatFood = true;
		if (rand() % 2)
			sounds[eat1].play(false);
		else 
			sounds[eat2].play(false);
		score += 10;
	}

	snake.paint(renderer, assets.texture, running, ground.grassColor);

	for (int i = 0; i < snake.size(); i++)
		while (snake[i] == food)
			food.spawn();
	food.paint(renderer, assets.texture, assets.food);

	displayInformation();
	SDL_RenderPresent(renderer);
}

void Game::loop()
{
	Uint32 frameStart, frameTime;
	SDL_Event event;
	
	paint();
	while (true)
	{
		frameStart = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
				break;
			}
			if (event.type == SDL_KEYDOWN)
				pollEvent(event);
		}
		
		if (isPause == false)	update();
	
		//delay per frame
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) 
			SDL_Delay(frameDelay - frameTime);

		//delay if snake dead
		if (!running)
		{
			SDL_Delay(400);
			break;
		}
	}

	saveHighestScore();
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}