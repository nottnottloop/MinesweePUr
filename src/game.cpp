#include "Game.hpp"
#include "Constants.hpp"
#include "Cell.hpp"

Game::Game() {
	initBoard();
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
		}
	}
}

Cell& Game::cell(int i, int j) {
	return cells_[i][j];
}