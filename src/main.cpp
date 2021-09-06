#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <array>

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

	std::vector<std::vector<Cell>> cells;

	//premature optimisation is the root of all fun
	cells.resize(8);
	for (int i = 0; i < 8; ++i) {
		cells[i].reserve(8);
	}

	constexpr float CELL_SCALE = 0.5f;
	constexpr float CENTER_X = (SCREEN_WIDTH / 2) - 64.0f * CELL_SCALE * 4;
	constexpr float CENTER_Y = (SCREEN_HEIGHT / 2) - 64.0f * CELL_SCALE * 4;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			cells[i].push_back(Cell({CENTER_X + 64.0f * CELL_SCALE * j, CENTER_Y + 64.0f * CELL_SCALE * i}, {0, 0, 64, 64}, bg, fg));
			cells[i][j].setScale(CELL_SCALE);
		}
	}

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
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				window.render(cells[i][j].renderRectInfo(), cells[i][j].getBgTex(), cells[i][j].getFgTex());
			}
		}
		window.display();
		//color used is just a random sequence of numbers that I got lucky with
		window.clear(12, 67, 114);
		window.showWindow();
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}