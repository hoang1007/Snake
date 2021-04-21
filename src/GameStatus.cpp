#include "Game.h"

void Game::Pause()
{
	isPause = true;
	//delay when open menu
	SDL_Delay(100);

	//clear screen
	clrscr(200);

	SDL_Color colorHomeButton = {255, 0, 0, 255};
	button[HOME].paint(renderer, colorHomeButton);

	SDL_Color colorQuitButton = {0, 255, 0, 255};
	button[QUIT].paint(renderer, colorQuitButton);
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

void Game::clear()
{
    snake.~Snake();
}