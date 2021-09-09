#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <array>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Cell.hpp"
#include "Constants.hpp"
#include "Game.hpp"
#include "Button.hpp"
#include "Text.hpp"

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

SDL_Color red = {255, 0, 0};
SDL_Color green = {0, 255, 0};
SDL_Color blue = {0, 0, 255};
SDL_Color cyan = {0, 255, 255};
SDL_Color white = {255, 255, 255};
SDL_Color black = {0, 0, 0};
Text text({650, 40}, {0, 0});

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has failed. sdl_error: " << SDL_GetError() << "\n";

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init has failed. Error: " << IMG_GetError() << "\n";

	if (TTF_Init())
		std::cout << "TTF_Init has failed. Error: " << TTF_GetError() << "\n";

#ifdef DEBUG_MINES
	Game game(8, 8, DEBUG_MINES);
#else
	Game game(8, 8, 10);
#endif

	Button restart_button({SCREEN_WIDTH / 2 - 64.0f, 0}, {0, 15}, {0, 0, 1024, 1024}, {0, 0, 1024, 1024}, nullptr, awesome, game, &Game::restart);
	restart_button.setScale(0.125f);
	buttons.push_back(&restart_button);


	bool quit = false;
	SDL_Event event;

	//attempt feebly to get rid of white flash on load
	window.clear();
	window.display();
	window.showWindow();
	text.loadFontTexture(FONT_LOCATION, FONT_SIZE, green, "Beginner");

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
							text.loadFontTexture(FONT_LOCATION, FONT_SIZE, green, "Beginner");
							text.setOffset({0, 0});
							game.clearBoard();
							#ifdef DEBUG_MINES
								game.setBoard(8, 8, DEBUG_MINES);
							#else
								game.setBoard(8, 8, 10);
							#endif
							restart_button.setOffset({0, 15});
							game.setCellScale(1.0f);
							game.setOffset({0, BEGINNER_OFFSET});
							game.initBoard();
							game.generateBoard();
							break;
						case SDLK_2:
							text.loadFontTexture(FONT_LOCATION, FONT_SIZE, cyan, "Medium");
							text.setOffset({0, -10});
							game.clearBoard();
							#ifdef DEBUG_MINES
								game.setBoard(16, 16, DEBUG_MINES);
							#else
								game.setBoard(16, 16, 40);
							#endif
							restart_button.setOffset({0, 5});
							game.setCellScale(0.6f);
							game.setOffset({0, MEDIUM_OFFSET});
							game.initBoard();
							game.generateBoard();
							break;
						case SDLK_3:
							text.loadFontTexture(FONT_LOCATION, FONT_SIZE, red, "Expert");
							text.setOffset({0, -10});
							game.clearBoard();
							#ifdef DEBUG_MINES
								game.setBoard(16, 30, DEBUG_MINES);
							#else
								game.setBoard(16, 30, 99);
							#endif
							restart_button.setOffset({0, 5});
							game.setCellScale(0.5f);
							game.setOffset({0, EXPERT_OFFSET});
							game.initBoard();
							game.generateBoard();
							break;
					}
			}
		}
		for (int i = 0; i < buttons.size(); ++i) {
			window.render(buttons[i]->renderFgRectInfo(), buttons[i]->getFgTex());
		}
		window.render(text);
		game.renderBoard();
		window.display();
		window.clear();
		window.showWindow();
	}

	window.cleanUp();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

	return 0;
}