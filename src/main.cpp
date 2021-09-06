#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Cell.hpp"
#include "Constants.hpp"

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has failed. sdl_error: " << SDL_GetError() << "\n";

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init has failed. Error: " << SDL_GetError() << "\n";

	RenderWindow window("MinesweePUr", SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Texture* bg = window.loadTexture("res/bg.png");
	SDL_Texture* fg = window.loadTexture("res/fg.png");

	Cell entity({50, 50}, bg, {0, 0, 128, 64}, fg);
	bool quit = false;

	SDL_Event event;

	//attempt feebly to get rid of white flash on load
	window.clear();
	window.display();
	window.showWindow();

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
					}
				break;
			}
		}
		window.render(entity, 0.5);
		window.display();
		//color used is just a random sequence of numbers
		window.clear(12, 67, 114);
		window.showWindow();
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}