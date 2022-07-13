#include <SDL2/SDL.h>

class Square
{
    public:
        Square(SDL_Renderer *renderer, int x, int y);
        ~Square();
        void render();
        void free();
        int mX;
        int mY;

    private:
        SDL_Renderer *mRenderer;
        int mWidth;
        int mHeight;
        SDL_Texture *mTexture;
};