#include <SDL.h>
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

	//numbers
	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			if (cells_[row][col].getValue() == fg_value::MINE) {
				continue;
			}
			int neighbour_mines = 0;
			//left
			if (col - 1 >= 0) {
				if (cells_[row][col - 1].getValue() == fg_value::MINE) {
					++neighbour_mines;
				}
			}
			//right
			if (col + 1 <= 7) {
				if (cells_[row][col + 1].getValue() == fg_value::MINE) {
					++neighbour_mines;
				}
			}
			//up
			if (row - 1 >= 0) {
				for (int i = -1; i < 2; ++i) {
					if (col + i < 0 || col + i > 7) {
						continue;
					}
					if (cells_[row - 1][col + i].getValue() == fg_value::MINE) {
						++neighbour_mines;
					}
				}
			}
			//down
			if (row + 1 <= 7) {
				for (int i = -1; i < 2; ++i) {
					if (col + i < 0 || col + i > 7) {
						continue;
					}
					if (cells_[row + 1][col + i].getValue() == fg_value::MINE) {
						++neighbour_mines;
					}
				}
			}
			if (neighbour_mines == 0) {
				cells_[row][col].setCellValue(fg_value::NONE);
			} else {
				cells_[row][col].setCellValue(static_cast<fg_value>(neighbour_mines - 1));
			}
		}
	}
}

Entity* Game::checkClick(Sint32 x, Sint32 y) {
	for (int row = 0; row < 8; ++row){
		for (int col = 0; col < 8; ++col){
			if (cells_[row][col].getPos().x < x && cells_[row][col].getPos().x + 64.0f * CELL_SCALE > x) {
				if (cells_[row][col].getPos().y < y && cells_[row][col].getPos().y + 64.0f * CELL_SCALE > y) {
					return &cells_[row][col];
				}
			}
		}
	}
	return nullptr;
}

Cell& Game::cell(int i, int j) {
	return cells_[i][j];
}