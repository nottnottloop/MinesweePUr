#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Constants.hpp"

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has failed. sdl_error: " << SDL_GetError() << "\n";

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init has failed. Error: " << SDL_GetError() << "\n";

	RenderWindow window("MinesweePUr", SCREEN_WIDTH, SCREEN_HEIGHT);

	bool quit = false;

	SDL_Event event;

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
		window.renderRect(255, 255, 255);
		window.display();
		window.clear();
		window.showWindow();
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}