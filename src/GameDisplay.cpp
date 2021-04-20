#include "Game.h"

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

void Game::clrscr(int opacity)
{
	SDL_Rect scr = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, opacity);
	SDL_RenderFillRect(renderer, &scr);
	//SDL_RenderPresent(renderer);
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
	SDL_Color pauseTutorialTextColor = {255, 255, 51, 255};
	
	int x = WALL_X + GRID + WALL_WIDTH;
	int y = SCREEN_HEIGHT / 2;

	text.display(renderer, "press p to pause!", x, y, pauseTutorialTextColor);
}