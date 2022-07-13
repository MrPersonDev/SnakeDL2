#include <SDL2/SDL.h>
#include <stdio.h>

#include "square.hpp"

Square::Square(SDL_Renderer *renderer, int x, int y)
{
	// Set member variables
	mRenderer = renderer;
	mX = x;
	mY = y;

	// Load the square image to a surface then to a texture
	SDL_Surface *loadedSurface = SDL_LoadBMP("resources/square.bmp");
	mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	// Get dimensions of the image
	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

	// Free the surface from memory
	SDL_FreeSurface(loadedSurface);
}

Square::~Square()
{
	free();
}

void Square::render()
{
	// Render at position (mX, mY)
	SDL_Rect renderQuad = {mX, mY, mWidth, mHeight};
	SDL_RenderCopy(mRenderer, mTexture, NULL, &renderQuad);
}

void Square::free()
{
	// Free from memory
	SDL_DestroyTexture(mTexture);
	mTexture = NULL;
	mRenderer = NULL;
	int mX = 0;
	int mY = 0;
	int mWidth = 0;
	int mHeight = 0;
}