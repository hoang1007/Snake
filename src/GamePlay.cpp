#include "Game.h"
#include "Console.h"
#include <iostream>

void Game::update()
{
	snake.move();

	if (food == snake.front())
	{
		snake.isEatFood = true;
		if (rand() % 2)
			sounds[SNAKE_EAT_1].play(false);
		else 
			sounds[SNAKE_EAT_2].play(false);
		score += 10;
	}

	for (int i = 0; i < snake.size(); i++)
		while (snake[i] == food)
			food.spawn();
	food.paint(renderer, assets.texture, assets.food);
	
	if (!snake.alive)
		sounds[SNAKE_DIE].play(false);

	snake.paint(renderer, assets.texture, ground.grassColor);

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
			else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (button[HOME].isClicked(x, y))
					unPause();
			}
		}
		
		if (!isPause) update();	// neu game khong tam dung thi tiep tuc cap nhat
	
		//delay per frame
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) // nau thoi gian load khung hinh nho hon do tre khung hinh
			SDL_Delay(frameDelay - frameTime);

		//delay if snake dead
		if (!snake.alive)
		{
			SDL_Delay(500);
			break;
		}
		else if (!running)
			break;
	}

	saveHighestScore();
	//snake.~Snake();
}

void Game::play()
{
	SDL_Event e;
	while (running)
	{
		if (firstRun)
		{
			init();
			loop();
			firstRun = false;
		}

		if (!snake.alive)
		{
			clrscr(100);

			SDL_Color c = {128, 255, 128, 255};
			button[RESTART].paint(renderer, c);

			SDL_Color d = {255, 255, 0, 255};
			button[QUIT].paint(renderer, d);
			SDL_RenderPresent(renderer);

			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
				{
					running = false;
					break;
				}
				if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					if (button[QUIT].isClicked(x, y))
					{
						running = false;
						break;
					}
					else if (button[RESTART].isClicked(x, y))
					{
						init();
						loop();
					}
				}

			}

		}
	}
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
			sounds[CHANGE_DIRECTION_UP].play(false);
		}
		break;
	case SDLK_s:
	case SDLK_DOWN:
		if (snake.preDir != Direction::up && !isPause)
		{
			snake.front().Dir = Direction::down;
			sounds[CHANGE_DIRECTION_DOWN].play(false);
		}
		break;
	case SDLK_a:
	case SDLK_LEFT:
		if (snake.preDir != Direction::right && !isPause)
		{
			snake.front().Dir = Direction::left;
			sounds[CHANGE_DIRECTION_LEFT].play(false);
		}
		break;
	case SDLK_d:
	case SDLK_RIGHT:
		if (snake.preDir != Direction::left && !isPause)
		{
			snake.front().Dir = Direction::right;
			sounds[CHANGE_DIRECION_RIGHT].play(false);
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