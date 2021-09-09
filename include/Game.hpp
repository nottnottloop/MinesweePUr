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
	bool cellRefPossible(int row, int col);
	fg_value determineCellValue(int row, int col);
	int checkNeighbours(int row, int col, fg_value val);
	void revealNeighbours(int row, int col);
	void checkLose(int row, int col);
	void lose();
	void checkWin();
	void win();
	void checkCellClick(Sint32 x, Sint32, bool right_mouse);
	Cell& cell(int i, int j);
private:
	std::vector<std::vector<Cell>> cells_;
	bool lost_;
};