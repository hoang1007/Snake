#include "Game.h"

void Game::paint()
{
	//xoa renderer
	SDL_SetRenderDrawColor(renderer, R_BACKGROUND, G_BACKGROUND, B_BACKGROUND, 255);
	SDL_RenderClear(renderer);

	ground.paint(renderer, assets.texture, assets.rock);
	snake.paint(renderer, assets.texture, ground.grassColor);
	food.paint(renderer, assets.texture, assets.food);

	displayInformation();

	SDL_RenderPresent(renderer);
}

void Game::clrscr(int opacity)
{
	SDL_Rect scr = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_SetRenderDrawColor(renderer, R_BACKGROUND, G_BACKGROUND, B_BACKGROUND, opacity);
	SDL_RenderFillRect(renderer, &scr);
	//SDL_RenderPresent(renderer);
}

void Game::displayInformation()
{
	// khai bao mau cho cac text
	const SDL_Color scoreColor = {255, 31, 31, 255},
					highestScoreColor = {51, 25, 0, 255};

	//dat toa do de hien thi text
	int score_x = WALL_WIDTH + WALL_X + GRID,
		score_y = WALL_Y + GRID;
	text.display(renderer, "SCORE: " + to_string(score), score_x, score_y, scoreColor);

	int highestScore_x = score_x,
		highestScore_y = score_y + 2 * GRID;
	text.display(renderer, "Highest Score: " + to_string(highestScore), highestScore_x, highestScore_y, highestScoreColor);


	// hien thi huong dan tam dung game
	SDL_Color pauseTutorialTextColor = {255, 255, 51, 255};
	
	int x = WALL_X + GRID + WALL_WIDTH;
	int y = SCREEN_HEIGHT / 2;

	text.display(renderer, "press p to pause!", x, y, pauseTutorialTextColor);
}