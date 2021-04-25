#define SDL_MAIN_HANDLED
#include "Game.hpp"
#include "Button.hpp"

int main(int argc, char *argv[])
{
	Game game;
	game.init();
	game.loop();
}