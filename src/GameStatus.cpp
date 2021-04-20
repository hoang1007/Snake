#include "Game.h"

void Game::Pause()
{
	isPause = true;
	//delay when open menu
	SDL_Delay(100);

	//clear screen
	clrscr(200);

	SDL_Color colorPauseButton = {255, 0, 0, 255};
	button[HOME].present(renderer, colorPauseButton);

	SDL_Color colorHomeButton = {0, 255, 0, 255};
	button[QUIT].present(renderer, colorHomeButton);
	SDL_RenderPresent(renderer);
}

void Game::unPause()
{
	SDL_Delay(100);
	button[HOME].erase();
	button[QUIT].erase();

	isPause = false;

	paint();
}