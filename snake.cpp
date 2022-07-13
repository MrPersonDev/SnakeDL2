#include <SDL2/SDL.h>
#include <vector>

#include "snake.hpp"

Snake::Snake() { }

Snake::~Snake()
{
	free();
}

void Snake::init(SDL_Renderer *renderer)
{
	// Create the initial snake body
	for(int i = 1; i < 6; i++)
	{
		mSquares.insert(mSquares.begin(), new Square(renderer, i*50, 400));
	}

	// Set some member variables
	mHeadX = 250;
	mHeadY = 400;
	mRenderer = renderer;
}

void Snake::move(Direction dir)
{
	int newX = mHeadX;
	int newY = mHeadY;

	// Change new position based on movement direction
	switch(dir)
	{
		case UP:
			newY -= 50;
			break;
		case DOWN:
			newY += 50;
			break;
		case LEFT:
			newX -= 50;
			break;
		case RIGHT:
			newX += 50;
			break;
	}

	// Create a new square for the snake body
	mSquares.insert(mSquares.begin(), new Square(mRenderer, newX, newY));
	mHeadX = newX;
	mHeadY = newY;
}

bool Snake::snakeAtPos(int x, int y)
{
	// For each square in mSquares
	for(auto square : mSquares)
	{
		// Check if any part of the snake besides the head is at the given coords
		if(square != mSquares[0] && square->mX == x && square->mY == y)
		{
			return true;
		}
	}

	return false;
}

CollisionType Snake::collide(int appleX, int appleY)
{
	// Check if head collided with another part of snake
	if(snakeAtPos(mHeadX, mHeadY))
	{
		return SNAKE;
	}

	// Check if the head is out of bounds (hit a wall)
	if(mHeadX > 15*50 || mHeadX < 0 || mHeadY > 15*50 || mHeadY < 0)
	{
		return WALL;
	}

	// Check if the head is within the apple
	if(mHeadX == appleX && mHeadY == appleY)
	{
		return APPLE;
	}

	return NONE;
}

void Snake::removeTail()
{
	// Free the last element then remove it from the vector
	mSquares.back()->free();
	mSquares.pop_back();
}

void Snake::render()
{
	// Render each square in mSquares
	for(auto square : mSquares)
	{
		square->render();
	}
}

void Snake::free()
{
	// Free each square in mSquares
	for(auto square : mSquares)
	{
		square->free();
	}

	mHeadX = 0;
	mHeadY = 0;
}