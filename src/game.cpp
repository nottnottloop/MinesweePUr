#include <random>
#include "Game.hpp"
#include "Constants.hpp"
#include "Cell.hpp"

std::random_device rds;
std::mt19937_64 rd(rds());

Game::Game() {
	initBoard();
	generateBoard();
}

void Game::initBoard() {
	//premature optimisation is the root of all fun
	//code below heavily assumes an 8x8 board
	cells_.resize(8);
	for (int i = 0; i < 8; ++i) {
		cells_[i].reserve(8);
	}

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			cells_[i].emplace_back(Cell({CENTER_X + 64.0f * CELL_SCALE * j, CENTER_Y + 64.0f * CELL_SCALE * i}, {0, 0, 64, 64}, {0, 0, 64, 64}, bg, fg));
			cells_[i][j].setScale(CELL_SCALE);
			cells_[i][j].setCellValue(fg_value::NONE);
		}
	}
}

void Game::generateBoard() {
	//mines
	for (int i = 0; i < NUM_MINES; ++i) {
		for (;;) {
			int row = rd() % 8;
			int col = rd() % 8;
			if (cells_[row][col].getValue() == fg_value::MINE) {
				continue;
			}
			cells_[row][col].setCellValue(fg_value::MINE);
			break;
		}
	}
}

Cell& Game::cell(int i, int j) {
	return cells_[i][j];
}