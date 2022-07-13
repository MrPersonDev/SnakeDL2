#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "counter.hpp"

Counter::Counter() { }

Counter::~Counter()
{
	free();
}

void Counter::init(SDL_Renderer *renderer)
{
	// Set member variables
	mFont = TTF_OpenFont("resources/meslo.ttf", 48);
	mRenderer = renderer;
	mCount = 0;
}

void Counter::increase()
{
	mCount++;
}

void Counter::render()
{
	// White
	SDL_Color textColour = {255, 255, 255};

	// Load a surface with the counter converted to a char pointer then create a texture with it
	SDL_Surface *textSurface = TTF_RenderText_Solid(mFont, std::to_string(mCount).c_str(), textColour);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer, textSurface);

	// Get dimensions from surface
	int width = textSurface->w;
	int height = textSurface->h;

	// Free surface from memory
	SDL_FreeSurface(textSurface);

	// Render at top middle of screen
	SDL_Rect renderQuad = {400-(width/2.0), 2, width, height};
	SDL_RenderCopy(mRenderer, texture, NULL, &renderQuad);
}

void Counter::free()
{
	// Free from memory
	TTF_CloseFont(mFont);
	mFont = NULL;
	mRenderer = NULL;
	mCount = 0;
}
