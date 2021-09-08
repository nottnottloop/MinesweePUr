#pragma once
#include <SDL.h>
#include <vector>
#include <Cell.hpp>

extern SDL_Texture* bg;
extern SDL_Texture* fg;

class Game {
public:
	Game();
	void initBoard();
	Cell& cell(int i, int j);
private:
	std::vector<std::vector<Cell>> cells_;
};