#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include "snake.hpp"
#include "apple.hpp"
#include "counter.hpp"

void init();
void close();

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Renderer *gRenderer = NULL;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

Snake gSnake;
Apple gApple;
Counter gCounter;

const int MOVE_DELAY = 7;

int main(int agrc, int args[])
{
	init();

	// Variables for game loop
	bool quit = false;
	SDL_Event e;
	int framesSinceUpdate = 0;
	Direction lastDir = RIGHT;
	Direction currentDir = RIGHT;

	// Game loop
	while(!quit)
	{
		long start = SDL_GetPerformanceCounter();

		// Handle events
		while(SDL_PollEvent(&e) != 0)
		{
			// SDL_QUIT is for events such as pressing alt-f4 or clicking 'X' button
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		// Handle keyboard input
		// Check last direction to insure the snake does not go through itself
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if(currentKeyStates[SDL_SCANCODE_UP] && lastDir != DOWN)
		{
			currentDir = UP;
		}
		else if(currentKeyStates[SDL_SCANCODE_DOWN] && lastDir != UP)
		{
			currentDir = DOWN;
		}
		else if(currentKeyStates[SDL_SCANCODE_LEFT] && lastDir != RIGHT)
		{
			currentDir = LEFT;
		}
		else if(currentKeyStates[SDL_SCANCODE_RIGHT] && lastDir != LEFT)
		{
			currentDir = RIGHT;
		}

		// MOVE_DELAY ms between position updates
		if(framesSinceUpdate > MOVE_DELAY)
		{
			gSnake.move(currentDir);
			lastDir = currentDir;
			framesSinceUpdate = 0;

			// Check collisions
			CollisionType collision = gSnake.collide(gApple.mX, gApple.mY);
			if(collision == APPLE)
			{
				// Eat an apple
				gCounter.increase();
				gApple.move(&gSnake);
			}
			else if(collision == WALL || collision == SNAKE)
			{
				// Die
				break;
			}
			else
			{
				gSnake.removeTail();
			}
		}
		else
		{
			framesSinceUpdate++;
		}

		// Clear screen
		SDL_RenderClear(gRenderer);

		// Render classes
		gSnake.render();
		gApple.render();
		gCounter.render();

		// Update screen
		SDL_RenderPresent(gRenderer);

		// Calculations to cap framerate at 60fps without vsync
		long end = SDL_GetPerformanceCounter();
		float msElapsed = (end - start) / float(SDL_GetPerformanceFrequency() * 1000.0);
		SDL_Delay(16.7 - msElapsed);
	}

	close();
}

void init()
{
	// Initialize window and renderer
	gWindow = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, 0);

	// Initialize true type fonts
	TTF_Init();

	// Initialize classes with renderer
	gSnake.init(gRenderer);
	gApple.init(gRenderer);
	gCounter.init(gRenderer);

	// Move the apple to a random position
	gApple.move(&gSnake);
}

void close()
{
	// Destroy window and renderer
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
	gRenderer = NULL;

	// Free classes
	gSnake.free();
	gApple.free();
	gCounter.free();

	// Quit the game
	SDL_Quit();
}
