#pragma once
#include <SDL.h>
#include <vector>
#include <Cell.hpp>
#include "Constants.hpp"

class Game {
public:
	Game();
	void initBoard();
	Cell& cell(int i, int j);
private:
	std::vector<std::vector<Cell>> cells_;
};