# SnakeDL2
#### Video Demo: https://youtube.com/watch?v=amongusfortniteimpostersussy
## Description:
**What is SDL2?**\
This project uses a development library called Simple Directmedia Layer 2, or SDL2 for short. Though SDL2 has bindings for many languages, including C# and Python, I decided to use C++. SDL2 allows low level access to input, audio and graphics hardware, and has been used for many games such as FTL, Factorio, Team Fortress 2, Counter-Strike: Global Offensive and Half Life 2.

### **How to download and play the game:**
1. Download the source:
   * Either go to https://github.com/MrPersonDev/SnakeDL2/Releases and click on the latest source code release. After downloading the zip file, extract it.
   * Or from your terminal emulator of choice, run `git clone https://github.com/MrPersonDev/SnakeDL2`
2. Once you have the source you might be able to just run it, I don't really know. Good luck.
3. Use the arrow keys (<kbd>↑</kbd>, <kbd>↓</kbd>, <kbd>←</kbd>, <kbd>→</kbd>) to change the snake's direction. The green squares are your snake and the red squares are apples which give you points and increase the size of your snake. Don't run into your own tail or the walls because then you will die and the game will be over. If you have a 60% keyboard (or worse), good luck holding down <kbd>fn</kbd> the whole game.
4. There's a score counter at the top center of the screen, you want that number to be higher.

### **How does the game work:**\
Since this is made in C++, the code has to be as abstracted as possible to make it much harder to find bugs in the code. (I guess it also makes it a little easier to read) Due to this, the game is separated into main.cpp + 4 classes.

`main.cpp` is where most of the game's logic is found. It starts by including some header files and declaring some variables. `void init()` is called at the start of `int main()`. This function is used to create the window and renderer from which the game is drawn. It also initializes SDL's TTF functionality and gives some other classes a pointer to the game's renderer. The entire game runs within a while loop which loops until the game is closed from <kbd>alt</kbd>+<kbd>f4</kbd> or clicking the 'X' button. Within the game loop, first, keyboard input is checked, then collisions are checked and managed accordingly and finally the game is renderer. There is also some code to cap the framerate at 60fps, otherwise the game would run at different speeds for every player. At the end of `int main()`, the window, renderer and classes are all free'd from memory using the `void close()` function.

`snake.cpp` also has holds a lot of the game's functionality. It utilizes an `std::vector` containing a Square class for each square in the snake's body. When initialized the snake generates a starting body of five squares. In the `void Snake::move()` function, it creates a new snake body part depending on which the keyboard input received from `int main()`. There are also two functions for collision: `bool Snake::snakeAtPos()` and `CollisionType Snake::collide()`. `snakeAtPos()` iterates through each square in the snake's body and checks if there is a snake part located at the given coordinates. `collide()` checks for the three types of collisions and returns a `CollisionType` which is an enum defined in `snake.hpp`. `void Snake::removeTail()` does exactly as the name suggests. `void Snake::render()` renders each of the Square classes in the snake's body. Finally, `void Snake::free()` free the snake from memory.

`square.cpp` is a class used by the Snake class to render a piece of the snake's body at a given position. In the constructor, it loads an `SDL_Surface` with the `square.bmp` image and creates a texture using the surface. This texture is later renderered in `void Square::render()`, which creates an `SDL_Rect` in order to render with the correct position and height.

`apple.cpp` is a class used to randomly position the apple, and render it. The `void Apple::init()` function is used to get the texture just like in `square.cpp`'s constructor. `void Apple::render()` is also the same as `square.cpp`. `void Apple::move()` is used to select a random position on the tilemap that is not taken by the snake's body. It does this using `rand()` from `<stdlib.h>`, and checking if the snake is at the new position using `snake.cpp`'s `bool Snake::snakeAtPos()` function.

The final class is `counter.cpp`, which is used to keep track and render text containing the player's score. `void Counter::init()` is used to load the font, `void Counter::increase()` increases the player's score by one and `void Counter::render()` renders the text to the screen. `render()` works by using `TTF_RenderText_Solid()` to render a text surface given a font, some text and a colour. The surface is then converted to a texture. Just like with all the other `render()` functions, this one uses an `SDL_Rect` to render the texture at a position, and here it is renderer at the top middle of the screen.

There is also one last file named `Makefile` which is what runs when I type `make` into my terminal. It just compiles the game to an executable like we had to do in week 1-5 psets and labs.
