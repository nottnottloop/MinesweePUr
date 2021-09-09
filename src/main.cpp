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

std::vector<Button*> buttons;

void checkButtonClick(Sint32 x, Sint32 y, bool right_mouse) {
	for (int i = 0; i < buttons.size(); ++i) {
		if (buttons[i]->getPos().x < x && buttons[i]->getPos().x + buttons[i]->getFgFrame().w * buttons[i]->getScale() > x) {
			if (buttons[i]->getPos().y < y && buttons[i]->getPos().y + buttons[i]->getFgFrame().h * buttons[i]->getScale() > y) {
				if (right_mouse) {
					buttons[i]->rightClick();
				} else {
					buttons[i]->leftClick();
				}
			}
		}
	}
}

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

	Button restart_button({SCREEN_WIDTH / 2 - 64.0f, 15}, {0, 0, 1024, 1024}, {0, 0, 1024, 1024}, nullptr, awesome, game, &Game::restart);
	restart_button.setScale(0.125f);
	buttons.push_back(&restart_button);

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
							checkButtonClick(event.button.x, event.button.y, false);
							break;
						case SDL_BUTTON_RIGHT:
							game.checkCellClick(event.button.x, event.button.y, true);
							checkButtonClick(event.button.x, event.button.y, true);
							break;
							break;
					}
				break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_r:
							game.restart();
							break;
						case SDLK_1:
							game.clearBoard();
							#ifdef DEBUG_MINES
								game.setBoard(8, 8, DEBUG_MINES);
							#else
								game.setBoard(8, 8, 10);
							#endif
							restart_button.setOffset({0, 15});
							game.setCellScale(1.0f);
							game.setYOffset(BEGINNER_OFFSET);
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
							restart_button.setOffset({0, 5});
							game.setCellScale(0.6f);
							game.setYOffset(MEDIUM_OFFSET);
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
							restart_button.setOffset({0, 5});
							game.setCellScale(0.5f);
							game.setYOffset(EXPERT_OFFSET);
							game.initBoard();
							game.generateBoard();
							break;
					}
			}
		}
		for (int i = 0; i < buttons.size(); ++i) {
			window.render(buttons[i]->renderFgRectInfo(), buttons[i]->getFgTex());
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