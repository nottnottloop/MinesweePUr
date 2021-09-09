#pragma once
#include <SDL.h>
#include <vector>
#include <Cell.hpp>
#include "Constants.hpp"

class Game {
public:
	Game(int rows, int cols, int mines);
	int getRows();
	int getCols();
	int getMines();
	void setCellScale(float scale);
	void setBoard(int rows, int cols, int mines);
	void clearBoard();
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
	void renderBoard();
	void renderButtons();
private:
	int board_rows_;
	int board_cols_;
	int mines_;
	bool won_;
	bool lost_;
	std::vector<std::vector<Cell>> cells_;
};