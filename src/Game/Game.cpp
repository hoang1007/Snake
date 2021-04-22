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

int Center(int a, int b, int w)
{
	return (a + b - w) / 2;
}
void Game::displayInformation()
{
	// display score
	const SDL_Color scoreColor = {255, 31, 31, 255},
					highestScoreColor = {51, 25, 0, 255};

	
	text.setColor(255, 31, 31, 255);
	text.loadText(renderer, "SCORE: " + to_string(score));
	//can giua 
	int score_x = Center(WALL_X + WALL_WIDTH, SCREEN_WIDTH, text.getWidth()),
		score_y = WALL_Y + GRID;

	// xoa text score cu
	SDL_Rect oldText = {WALL_X + WALL_WIDTH + GRID, score_y, SCREEN_WIDTH - WALL_X - WALL_WIDTH, text.getHeight()};
	SDL_SetRenderDrawColor(renderer, R_BACKGROUND, G_BACKGROUND, B_BACKGROUND, 255);
	SDL_RenderFillRect(renderer, &oldText);

	text.render(renderer, score_x, score_y);	

	// ve highest score text
	text.setColor(51, 25, 0, 255);
	text.loadText(renderer, "Highest Score: " + to_string(highestScore));

	//can giua
	int highestScore_x = Center(WALL_X + WALL_WIDTH, SCREEN_WIDTH, text.getWidth()),
		highestScore_y = score_y + 2 * GRID;

	text.render(renderer, highestScore_x, highestScore_y);

	// //display pause game tutorial

	text.setColor(255, 255, 51, 255);
	text.loadText(renderer, "press p to pause!");
	int pauseTutorialText_x = Center(WALL_X + WALL_WIDTH, SCREEN_WIDTH, text.getWidth()),
		pauseTutorialText_y = SCREEN_HEIGHT / 2;

	text.render(renderer, pauseTutorialText_x, pauseTutorialText_y);
}

void Game::Pause()
{
	isPause = true;
	//delay when open menu
	SDL_Delay(100);
}

void Game::unPause()
{
	SDL_Delay(100);
	isPause = false;
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