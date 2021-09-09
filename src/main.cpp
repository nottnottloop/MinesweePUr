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
#include "Button.hpp"

//system variables
//int SCREEN_WIDTH = 640;
//int SCREEN_HEIGHT = 480;
int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 768;

//DEBUG
//#define DEBUG_MINES 99

RenderWindow window = RenderWindow("MinesweePUr", SCREEN_WIDTH, SCREEN_HEIGHT);
SDL_Texture* bg = window.loadTexture("res/bg.png");
SDL_Texture* fg = window.loadTexture("res/fg.png");
SDL_Texture* awesome = window.loadTexture("res/awesome.png");

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has failed. sdl_error: " << SDL_GetError() << "\n";

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init has failed. Error: " << SDL_GetError() << "\n";

#ifdef DEBUG_MINES
	Game game(8, 8, DEBUG_MINES);
#else
	Game game(8, 8, 10);
#endif

	std::vector<Button*> buttons;
	//Button restart_button({SCREEN_WIDTH / 2 - 64.0f, 100}, {0, 0, 128, 128}, {0, 0, 128, 128}, awesome, awesome, game);

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
							#ifdef DEBUG_MINES
								game.setBoard(8, 8, DEBUG_MINES);
							#else
								game.setBoard(8, 8, 10);
							#endif
							game.setCellScale(0.75f);
							game.initBoard();
							game.generateBoard();
							break;
						case SDLK_2:
							game.clearBoard();
							#ifdef DEBUG_MINES
								game.setBoard(16, 16, DEBUG_MINES);
							#else
								game.setBoard(16, 16, 40);
							#endif
							game.setCellScale(0.6f);
							game.initBoard();
							game.generateBoard();
							break;
						case SDLK_3:
							game.clearBoard();
							#ifdef DEBUG_MINES
								game.setBoard(16, 30, DEBUG_MINES);
							#else
								game.setBoard(16, 30, 99);
							#endif
							game.setCellScale(0.5f);
							game.initBoard();
							game.generateBoard();
							break;
					}
			}
		}
		game.renderBoard();
		//for (int i = 0; i < buttons.size(); ++i) {
		//	window.render(buttons[i]->renderFgRectInfo(), buttons[i]->getFgTex());
		//}
		window.display();
		window.clear();
		window.showWindow();
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}