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
	//code below heavily assumes an 8x8 board
	cells.resize(8);
	for (int i = 0; i < 8; i++) {
		cells[i].reserve(8);
	}

	constexpr float CELL_SCALE = 0.7f;
	constexpr float CENTER_X = (SCREEN_WIDTH / 2) - 64.0f * CELL_SCALE * 4;
	constexpr float CENTER_Y = (SCREEN_HEIGHT / 2) - 64.0f * CELL_SCALE * 4;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cells[i].push_back(Cell({CENTER_X + 64.0f * CELL_SCALE * j, CENTER_Y + 64.0f * CELL_SCALE * i}, {0, 0, 64, 64}, {0, 0, 64, 64}, bg, fg));
			cells[i][j].setScale(CELL_SCALE);
		}
	}

	bool quit = false;
	SDL_Event event;

	//attempt feebly to get rid of white flash on load
	window.clear();
	window.display();
	window.showWindow();
int rainbow_start[8][8] =
{
	{0, 1, 2, 3, 4, 5, 6, 7},
	{1, 2, 3, 4, 5, 6, 7, 8},
	{2, 3, 4, 5, 6, 7, 8, 9},
	{3, 4, 5, 6, 7, 8, 9, 0},
	{4, 5, 6, 7, 8, 9, 0, 1},
	{5, 6, 7, 8, 9, 0, 1, 2},
	{6, 7, 8, 9, 0, 1, 2, 3},
	{7, 8, 9, 0, 1, 2, 3, 4}
};

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
		//just for amusement

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				window.render(cells[i][j].renderBgRectInfo(), cells[i][j].getBgTex());
				if (cells[i][j].shown()) {
					cells[i][j].changeCellValue(static_cast<value>(rainbow_start[i][j]));
					rainbow_start[i][j]--;
					if (rainbow_start[i][j] < 0) {
						rainbow_start[i][j] = 9;
					}
					window.render(cells[i][j].renderFgRectInfo(), cells[i][j].getFgTex());
				}
			}
		}
		window.display();
		//color used is just a random sequence of numbers that I got lucky with
		SDL_Delay(500);
		window.clear();
		window.showWindow();
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}