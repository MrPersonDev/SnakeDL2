#include <SDL2/SDL.h>

#include "snake.hpp"

class Apple
{
    public:
        Apple();
        ~Apple();
        void init(SDL_Renderer *renderer);
        void render();
        void move(Snake *snake);
        void free();
        int mX;
        int mY;

    private:
        SDL_Texture *mTexture;
        SDL_Renderer *mRenderer;
        int mWidth;
        int mHeight;
};
