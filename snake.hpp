#pragma once
#include <SDL2/SDL.h>
#include <vector>

#include "square.hpp"

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum CollisionType
{
    NONE,
    APPLE,
    SNAKE,
    WALL
};

class Snake
{
    public:
        Snake();
        ~Snake();
        void init(SDL_Renderer *renderer);
        void move(Direction dir);
        bool snakeAtPos(int x, int y);
        CollisionType collide(int appleX, int appleY);
        void removeTail();
        void render();
        void free();

    private:
        SDL_Renderer *mRenderer;
        std::vector<Square*> mSquares;
        int mHeadX;
        int mHeadY;
        bool mTilemap[16][16];
};