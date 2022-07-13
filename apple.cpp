#include <SDL2/SDL.h>
#include <stdlib.h>

#include "apple.hpp"
#include "snake.hpp"

Apple::Apple() { }

Apple::~Apple()
{
	free();
}

void Apple::init(SDL_Renderer *renderer)
{
	// Load apple image to a surface then create a texture with it
	SDL_Surface *loadedSurface = SDL_LoadBMP("resources/apple.bmp");
	mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	// Get dimensions from surface
	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

	// Free surface from memory
	SDL_FreeSurface(loadedSurface);

	// Set member variables
	mRenderer = renderer;
}

void Apple::render()
{
	// Render at position (mX, mY)
	SDL_Rect renderQuad = {mX, mY, mWidth, mHeight};
	SDL_RenderCopy(mRenderer, mTexture, NULL, &renderQuad);
}

void Apple::move(Snake *snake)
{
	// Keep selecting a random position until it is not colliding with the snake
	int newX;
	int newY;
	do
	{
		newX = (rand() % 16) * 50;
		newY = (rand() % 16) * 50;
	}
	while(snake->snakeAtPos(newX, newY));

	// Move to the new random position
	mX = newX;
	mY = newY;
}

void Apple::free()
{
	// Free from memory
	SDL_DestroyTexture(mTexture);
	mTexture = NULL;
	mRenderer = NULL;
	mX = 0;
	mY = 0;
	mWidth = 0;
	mHeight = 0;
}
