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
			else
			{
				SDL_SetRenderDrawColor(renderer, R_BACKGROUND, G_BACKGROUND, B_BACKGROUND, 255);
				SDL_RenderClear(renderer);
			}
		}
		init();
	}
}

void Game::init()
{
	assets = Assets();
	assets.load("game.png", renderer);
	
	int fontSize = 45;
	text = Text("font.ttf", fontSize);

	snake = Snake(4, assets.Snake);

	map = Map();

	food = Food();

	running = true;
	isPause = false;

	score = 0;
	highestScore = getHighestScore();	//get highest score from file

	//present snake, food and map
	map.paint(renderer, assets.texture, assets.wall);
	snake.paint(renderer, assets.texture, running, map.grassColor);
	food.paint(renderer, assets.texture, assets.food);

	SDL_RenderPresent(renderer);
}

void Game::pollEvent(SDL_Event& event)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_w:
	case SDLK_UP:
		if (snake.preDir != Direction::down)
			snake.front().Dir = Direction::up;
		break;
	case SDLK_s:
	case SDLK_DOWN:
		if (snake.preDir != Direction::up)
			snake.front().Dir = Direction::down;
		break;
	case SDLK_a:
	case SDLK_LEFT:
		if (snake.preDir != Direction::right)
			snake.front().Dir = Direction::left;
		break;
	case SDLK_d:
	case SDLK_RIGHT:
		if (snake.preDir != Direction::left)
			snake.front().Dir = Direction::right;
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

void Game::displayScore()
{
	const SDL_Color scoreColor = {255, 0, 0, 255},
					highestScoreColor = {51, 25, 0, 255};
	//set width and height enough to erase old render text
	SDL_Rect scoreFrame = {WALL_X + WALL_WIDTH + 2 * GRID, WALL_Y + GRID, 5 * GRID, 5 * GRID};
	text.display(renderer, "SCORE: " + to_string(score), scoreColor, scoreFrame);

	SDL_Rect highestScoreFrame = {scoreFrame.x, scoreFrame.y + 50, scoreFrame.w, scoreFrame.h};
	text.display(renderer, "Highest Score: " + to_string(highestScore), highestScoreColor, highestScoreFrame);
}

void Game::Pause()
{
	isPause = true;
}
void Game::unPause()
{
	isPause = false;
}

void Game::update()
{
	if (snake.move() == false)
			running = false;

	if (food == snake.front())
	{
		snake.isEatFood = true;
		score += 10;
	}

	snake.paint(renderer, assets.texture, running, map.grassColor);

	for (int i = 0; i < snake.size(); i++)
		while (snake[i] == food)
			food.spawn();
	food.paint(renderer, assets.texture, assets.food);

	displayScore();
	SDL_RenderPresent(renderer);
}

void Game::loop()
{
	Uint32 frameStart, frameTime;
	SDL_Event event;

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
			pollEvent(event);
		}
		
		if (isPause == false)	update();

		if (!running)
		{
			SDL_Delay(400);
			break;
		}
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) 
			SDL_Delay(frameDelay - frameTime);
	}

	saveHighestScore();
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}