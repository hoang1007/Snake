#include "Game.hpp"
#include "Console.hpp"

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
			else SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		}
	}
}

void Game::textInit()
{
	const string path = "font.ttf";

	text[SCORE] = Text(path, 50);

	text[HIGHEST_SCORE] = Text(path, 50);

	text[PAUSE_TUTORIAL] = Text(path, 60);
	text[PAUSE_TUTORIAL].setStyle(TTF_STYLE_ITALIC);

	text[LOSE] = Text(path, 100);
	text[LOSE].setStyle(TTF_STYLE_BOLD);

	// đặt màu cho các text
	text[SCORE].setColor(255, 31, 31, 255);
	text[HIGHEST_SCORE].setColor(51, 25, 0, 255);
	text[PAUSE_TUTORIAL].setColor(255, 255, 51, 255);
	text[LOSE].setColor(255, 0, 0, 255);
}

void Game::soundsInit()
{
	sounds[CHANGE_DIRECTION_UP] = Media("sounds/up.wav");

	sounds[CHANGE_DIRECTION_DOWN] = Media("sounds/down.wav");

	sounds[CHANGE_DIRECTION_LEFT] = Media("sounds/left.wav");

	sounds[CHANGE_DIRECTION_RIGHT] = Media("sounds/right.wav");

	sounds[SNAKE_EAT_1] = Media("sounds/eat1.wav");

	sounds[SNAKE_EAT_2] = Media("sounds/eat2.wav");

	sounds[SNAKE_DIE] = Media("sounds/die.wav");
}

void Game::resourceInit()
{
	const int SIZE = assets.getWidth() / 4;
	food.resource = { SIZE, SIZE, SIZE, SIZE };
	ground.rockSrc = { 2 * SIZE, SIZE, SIZE, SIZE };
	restartButton.resource = { 3 * SIZE, SIZE, SIZE, SIZE };

	snake.src[HEAD] = { 0, 0, SIZE, SIZE };
	snake.src[TAIL] = { SIZE, 0, SIZE, SIZE };
	snake.src[CRASH] = { 2 * SIZE, 0, SIZE, SIZE };
	snake.src[BODY] = { 3 * SIZE, 0, SIZE, SIZE };
	snake.src[CORNER] = { 0, SIZE, SIZE, SIZE };
}

void Game::init()
{
	frameDelay = 5000 / FPS;

	assets = Assets();
	assets.load("assets.png", renderer);
		
	pauseSprite = Assets();
	pauseSprite.load("pause.png", renderer);

	snake = Snake(5);	// khởi tạo rắn với chiều dài mặc định là 5

	ground = Ground();

	food = Food();

	restartButton = Button();

	soundsInit();
	resourceInit();
	textInit();

	running = true;
	isPause = false;

	score = 0;
	highestScore = getHighestScore();	// lấy điểm cao nhất từ file
}

void Game::paint()
{
	// xóa render cũ
	SDL_SetRenderDrawColor(renderer, R_BACKGROUND, G_BACKGROUND, B_BACKGROUND, 255);
	SDL_RenderClear(renderer);

	ground.paint(renderer, assets.texture);
	snake.paint(renderer, assets.texture, ground.grassColor);
	food.paint(renderer, assets.texture);
	displayInformation();

	SDL_RenderPresent(renderer);
}

Game::~Game()
{
	cerr << "Game destructor called!" << endl;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}