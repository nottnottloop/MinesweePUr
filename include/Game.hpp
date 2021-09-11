#pragma once
#include <SDL.h>
#include <vector>
#include <Cell.hpp>
#include "Constants.hpp"

class Game {
public:
	Game();
	Game(int rows, int cols, int mines);
	int getRows();
	int getCols();
	int getMines();
	void setCellScale(float scale);
	void setOffset(Vector2f offset);
	void setBoard(int rows, int cols, int mines);
	void toggleMute();
	bool getMute();
	void restart();
	void clearBoard();
	void initBoard();
	void generateBoard();
	bool cellRefPossible(int row, int col);
	fg_value determineCellValue(int row, int col);
	int checkNeighbours(int row, int col, fg_value val);
	void revealNeighbours(int row, int col);
	int getRemaining();
	void checkLose(int row, int col);
	void lose();
	void checkWin();
	void win();
	void checkCellClick(Sint32 x, Sint32, bool right_mouse);
	Cell& cell(int i, int j);
	void renderBoard();
	void renderButtons();
private:
	Vector2f offset_;
	int board_rows_;
	int board_cols_;
	int mines_;
	bool won_;
	bool lost_;
	bool muted_;
	std::vector<std::vector<Cell>> cells_;
};