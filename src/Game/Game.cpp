#include "Game.hpp"
#include "Console.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Game::pollEvent(SDL_Event& event)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_w:
	case SDLK_UP:
			snake.nextDir = UP;
			sounds[CHANGE_DIRECTION_UP].play(false);
		break;
	case SDLK_s:
	case SDLK_DOWN:
			snake.nextDir = DOWN;
			sounds[CHANGE_DIRECTION_DOWN].play(false);
		break;
	case SDLK_a:
	case SDLK_LEFT:
			snake.nextDir = LEFT;
			sounds[CHANGE_DIRECTION_LEFT].play(false);
		break;
	case SDLK_d:
	case SDLK_RIGHT:
			snake.nextDir = RIGHT;
			sounds[CHANGE_DIRECTION_RIGHT].play(false);
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
	snake.move();
	if (!snake.alive)
		sounds[SNAKE_DIE].play(false);

	if (food == snake.front())
	{
		snake.isEatFood = true;
		sounds[rand() % 2 ? SNAKE_EAT_1 : SNAKE_EAT_2].play(false);
		score += 10;
	}

	snake.paint(renderer, assets.texture, ground.grassColor);

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
		
		if (!isPause)	update();
	
		//delay per frame
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) 
			SDL_Delay(frameDelay - frameTime);

		//delay if snake dead
		if (!snake.alive)
		{
			SDL_Delay(400);
			break;
		}
		if (!running) break;
	}

	saveHighestScore();
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}