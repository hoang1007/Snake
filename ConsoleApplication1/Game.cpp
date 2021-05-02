#include "Game.hpp"
#include "Console.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
void Game::pollEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			running = false;
			return;
		}
		if (snake.alive)
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_w:
				case SDLK_UP:
					if (!isPause)
						snake.nextDir = UP;
					sounds[CHANGE_DIRECTION_UP].play(false);
					break;
				case SDLK_s:
				case SDLK_DOWN:
					if (!isPause)
						snake.nextDir = DOWN;
					sounds[CHANGE_DIRECTION_DOWN].play(false);
					break;
				case SDLK_a:
				case SDLK_LEFT:
					if (!isPause)
						snake.nextDir = LEFT;
					sounds[CHANGE_DIRECTION_LEFT].play(false);
					break;
				case SDLK_d:
				case SDLK_RIGHT:
					if (!isPause)
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

// căn giữa hai biên a và b với khối có độ dài theo chiều muốn căn
int Center(int a, int b, int size)
{
	return (a + b - size) / 2;
}

void Game::displayInformation()
{	
	text[SCORE].free(renderer);	// xóa text score cũ (vì số điểm thay đổi thì chiều dài text sẽ thay đổi)
	
	text[SCORE].loadText(renderer, "SCORE: " + to_string(score));

	// căn giữa theo trục x
	int score_x = Center(WALL_X + WALL_WIDTH + GRID, SCREEN_WIDTH, text[SCORE].getWidth()),
		score_y = WALL_Y + GRID;

	// render text mới
	text[SCORE].render(renderer, score_x, score_y);	

	// render điểm cao nhất
	
	text[HIGHEST_SCORE].loadText(renderer, "Highest Score: " + to_string(highestScore));

	// căn giữa theo trục x
	int highestScore_x = Center(WALL_X + WALL_WIDTH + GRID, SCREEN_WIDTH, text[HIGHEST_SCORE].getWidth()),
		highestScore_y = score_y + 2 * GRID;

	text[HIGHEST_SCORE].render(renderer, highestScore_x, highestScore_y);

	//render text hướng dẫn dừng game
	text[PAUSE_TUTORIAL].loadText(renderer, "press p to pause!");
	int pauseTutorialText_x = Center(WALL_X + WALL_WIDTH + GRID, SCREEN_WIDTH, text[PAUSE_TUTORIAL].getWidth()),
		pauseTutorialText_y = SCREEN_HEIGHT / 2;
	//render text
	text[PAUSE_TUTORIAL].render(renderer, pauseTutorialText_x, pauseTutorialText_y);
}

void Game::Pause()
{
	isPause = true;
	clrscr(200);
	// hiển thị ảnh dừng game
	SDL_RenderCopy(renderer, pauseSprite.texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_Delay(100);
}

void Game::unPause()
{
	SDL_Delay(100);
	// vẽ lại màn hình
	paint();
	isPause = false;
}

void Game::update()
{
	snake.nextDir = snake.autoMove(food);
	snake.move();
	if (!snake.alive)
		sounds[SNAKE_DIE].play(false);

	if (food == snake.front())	// nếu ăn thức ăn thì cộng điểm
	{
		//snake.isEatFood = true;
		sounds[rand() % 2 ? SNAKE_EAT_1 : SNAKE_EAT_2].play(false);	// chơi một trong hai sounds effect
		score += 10;
	}

	snake.paint(renderer, assets.texture, ground.grassColor);

	// random tọa độ thức ăn sao cho không trùng với rắn
	for (int i = 0; i < snake.size(); i++)
		while (snake[i] == food)
			food.spawn();

	food.paint(renderer, assets.texture);

	displayInformation();
	SDL_RenderPresent(renderer);
}

void Game::loop()
{
	Uint32 frameStart, frameTime;	// đếm thời gian để chạy một khung hình từ đó tính ra thời gian trễ của mỗi khung hình
	paint();
	while (true)
	{
		frameStart = SDL_GetTicks();

		pollEvent();
		if (!isPause && snake.alive)	update();	// nếu không dừng thì tiếp tục game
	
		// thời gian chạy một khung hình
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) 
			SDL_Delay(frameDelay - frameTime);

		if (!snake.alive)
			break;
		if (!running) return;
	}
	
	saveHighestScore();
	restart();
}

void Game::clrscr(int opacity)
{
	SDL_Rect screen = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_SetRenderDrawColor(renderer, R_BACKGROUND, G_BACKGROUND, B_BACKGROUND, opacity);
	SDL_RenderFillRect(renderer, &screen);
}

void Game::restart()
{
	SDL_Delay(150);
	clrscr(150);
	// hiển thị thông báo thua 
	text[LOSE].loadText(renderer, "YOU LOSE!!!");

	// căn giữa cho text 
	int lose_x = Center(0, SCREEN_WIDTH, text[LOSE].getWidth()),
		lose_y = SCREEN_HEIGHT / 4;
	text[LOSE].render(renderer, lose_x, lose_y);

	// hiển thị điểm
	text[SCORE].loadText(renderer, "YOUR SCORE: " + to_string(score));

	//căn giữa 
	int score_x = Center(0, SCREEN_WIDTH, text[SCORE].getWidth()),
		score_y = SCREEN_HEIGHT / 2;
	text[SCORE].render(renderer, score_x, score_y);

	// hiển thị nút chơi lại
	//căn giữa
	int button_x = Center(0, SCREEN_WIDTH, restartButton.getWidth()),
		button_y = SCREEN_HEIGHT / 2;

	restartButton.setCoordinate(button_x, button_y);
	restartButton.resize(200, 200, true);	// chỉnh kích thước của nút lên 200 * 200

	restartButton.paint(renderer, assets.texture);

	SDL_RenderPresent(renderer);

	SDL_Event e;
	while (SDL_WaitEvent(&e))
		if (e.type == SDL_QUIT)
		{
			running = false;
			return;
		}
}