#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <array>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Cell.hpp"
#include "Constants.hpp"
#include "Game.hpp"

//gameplay variables
int NUM_MINES = 3;

//system variables
//int SCREEN_WIDTH = 640;
//int SCREEN_HEIGHT = 480;
int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 768;

RenderWindow window = RenderWindow("MinesweePUr", SCREEN_WIDTH, SCREEN_HEIGHT);
SDL_Texture* bg = window.loadTexture("res/bg.png");
SDL_Texture* fg = window.loadTexture("res/fg.png");

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has failed. sdl_error: " << SDL_GetError() << "\n";

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init has failed. Error: " << SDL_GetError() << "\n";

	Game game(8, 8);

	bool quit = false;
	SDL_Event event;

	//attempt feebly to get rid of white flash on load
	window.clear();
	window.display();
	window.showWindow();

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					switch (event.button.button) {
						case SDL_BUTTON_LEFT:
							game.checkCellClick(event.button.x, event.button.y, false);
							break;
						case SDL_BUTTON_RIGHT:
							game.checkCellClick(event.button.x, event.button.y, true);
							break;
					}
				break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_r:
							game.clearBoard();
							game.initBoard();
							game.generateBoard();
							break;
						case SDLK_1:
							game.clearBoard();
							game.setBoard(8, 8);
							game.setCellScale(0.75f);
							game.initBoard();
							game.generateBoard();
							break;
						case SDLK_2:
							game.clearBoard();
							game.setBoard(16, 16);
							game.setCellScale(0.6f);
							game.initBoard();
							game.generateBoard();
							break;
						case SDLK_3:
							game.clearBoard();
							game.setBoard(16, 30);
							game.setCellScale(0.5f);
							game.initBoard();
							game.generateBoard();
							break;
					}
			}
		}
		game.renderBoard();
		window.display();
		window.clear();
		window.showWindow();
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}