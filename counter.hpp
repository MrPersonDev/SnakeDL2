#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Counter
{
	public:
		Counter();
		~Counter();
		void init(SDL_Renderer *renderer);
		void increase();
		void render();
		void free();

	private:
		TTF_Font *mFont;
		SDL_Renderer *mRenderer;
		int mCount;
};