#pragma once
#include <SDL.h>
#include <vector>
#include <Cell.hpp>
#include "Constants.hpp"

class Game {
public:
	Game();
	void initBoard();
	void generateBoard();
	int checkNeighbourMines(int row, int col);
	void revealNeighbours();
	void checkCellClick(Sint32 x, Sint32, bool right_mouse);
	Cell& cell(int i, int j);
private:
	std::vector<std::vector<Cell>> cells_;
};