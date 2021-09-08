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

RenderWindow window("MinesweePUr", SCREEN_WIDTH, SCREEN_HEIGHT);
SDL_Texture* bg = window.loadTexture("res/bg.png");
SDL_Texture* fg = window.loadTexture("res/fg.png");

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has failed. sdl_error: " << SDL_GetError() << "\n";

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init has failed. Error: " << SDL_GetError() << "\n";

	Game game;

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
						case SDL_BUTTON_LEFT: {
							Entity* ptr = game.checkClick(event.button.x, event.button.y);
							if (ptr != nullptr) {
								ptr->leftClick();
							}
						}
							break;
						case SDL_BUTTON_RIGHT: {
							Entity* ptr = game.checkClick(event.button.x, event.button.y);
							if (ptr != nullptr) {
								ptr->rightClick();
							}
						}
							break;
					}
				break;
			}
		}
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				window.render(game.cell(i, j).renderBgRectInfo(), game.cell(i, j).getBgTex());
				if (game.cell(i, j).fgShown()) {
					window.render(game.cell(i, j).renderFgRectInfo(), game.cell(i, j).getFgTex());
				}
			}
		}
		window.display();
		window.clear();
		window.showWindow();
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}