#pragma once
#include <SDL.h>
#include <vector>
#include <Cell.hpp>

class Game {
public:
	Game(SDL_Texture* bg, SDL_Texture* fg);
	void initBoard();
	Cell& cell(int i, int j);
private:
	SDL_Texture* bg_tex_;
	SDL_Texture* fg_tex_;
	std::vector<std::vector<Cell>> cells_;
};