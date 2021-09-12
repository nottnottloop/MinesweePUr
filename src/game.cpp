#include <SDL.h>
#include <SDL_mixer.h>
#include <random>
#include <vector>
#include <array>
#include <utility>
#include "Game.hpp"
#include "Constants.hpp"
#include "Cell.hpp"

std::random_device rds;
std::mt19937_64 rd(rds());

float center_x;
float center_y;
float cell_scale = 1.0f;

Game::Game() 
: board_rows_(0), board_cols_(0), lost_(false), won_(false), mines_(0), offset_({0, BEGINNER_OFFSET}), muted_(false) {
	initBoard();
	generateBoard();
}

Game::Game(int rows, int cols, int mines) 
: board_rows_(rows), board_cols_(cols), lost_(false), won_(false), mines_(mines), offset_({0, BEGINNER_OFFSET}), muted_(false) {
	initBoard();
	generateBoard();
}

int Game::getRows() {
	return board_rows_;
}

int Game::getCols() {
	return board_cols_;
}

int Game::getMines() {
	return mines_;
}

void Game::setCellScale(float scale) {
	cell_scale = scale;
}

void Game::setOffset(Vector2f offset) {
	offset_ = offset;
}

void Game::setBoard(int rows, int cols, int mines) {
	board_rows_ = rows;
	board_cols_ = cols;
	mines_ = mines;
}

void Game::toggleMute() {
	muted_ = !muted_;
}

bool Game::getMute() {
	return muted_;
}

void Game::restart() {
	if (!muted_) {
		Mix_PlayChannel(-1, click, 0);
	}
	clearBoard();
	initBoard();
	generateBoard();
}

void Game::clearBoard() {
	for (int i = 0; i < getRows(); ++i) {
		cells_[i].clear();
	}
	cells_.clear();
	lost_ = false;
	won_ = false;
}

void Game::initBoard() {
	center_x = (SCREEN_WIDTH / 2) - 60.0f * cell_scale * (getCols() / 2);
	center_y = (SCREEN_HEIGHT / 2) - 60.0f * cell_scale * (getRows() / 2);

	//premature optimisation is the root of all fun
	cells_.resize(getRows());
	for (int i = 0; i < getRows(); ++i) {
		cells_[i].reserve(getCols());
	}

	for (int i = 0; i < getRows(); ++i) {
		for (int j = 0; j < getCols(); ++j) {
			cells_[i].emplace_back(Cell({center_x + offset_.x + 60.0f * cell_scale * j, center_y + offset_.y + 60.0f * cell_scale * i}, {0, 0}, {0, 0, 60, 60}, {0, 0, 60, 60}, bg, fg));
		}
	}
}

void Game::generateBoard() {
	//mines
	for (int i = 0; i < getMines(); ++i) {
		for (;;) {
			int row = rd() % getRows();
			int col = rd() % getCols();
			if (cells_[row][col].getValue() == fg_value::MINE) {
				continue;
			}
			cells_[row][col].setCellValue(fg_value::MINE);
			printf("Mine: %d, %d\n", row, col);
			break;
		}
	}

	//numbers
	for (int row = 0; row < getRows(); ++row) {
		for (int col = 0; col < getCols(); ++col) {
			fg_value neighbour_mines = determineCellValue(row, col);
			cells_[row][col].setCellValue(neighbour_mines);
		}
	}
}

bool Game::cellRefPossible(int row, int col) {
	if (col < 0 || col > getCols() - 1 || row < 0 || row > getRows() - 1) {
		return false;
	} else {
		return true;
	}
}

fg_value Game::determineCellValue(int row, int col) {
	if (cells_[row][col].getValue() == fg_value::MINE) {
		return fg_value::MINE;
	}
	int neighbour_mines = checkNeighbours(row, col, fg_value::MINE);
	if (neighbour_mines == 0) {
		return fg_value::NONE;
	}
	//we subtract one from neighbour_mines because the enum doesn't cast perfectly
	return static_cast<fg_value>(neighbour_mines - 1);
}

int Game::checkNeighbours(int row, int col, fg_value val) {
	int neighbours = 0;
	//left
	if (cellRefPossible(row, col - 1)) {
		if (cells_[row][col - 1].getValue() == val) {
			++neighbours;
		}
	}
	//right
	if (cellRefPossible(row, col + 1)) {
		if (cells_[row][col + 1].getValue() == val) {
			++neighbours;
		}
	}
	//up
	if (cellRefPossible(row - 1, col)) {
		for (int i = -1; i < 2; ++i) {
			if (!cellRefPossible(row, col + i)) {
				continue;
			}
			if (cells_[row - 1][col + i].getValue() == val) {
				++neighbours;
			}
		}
	}
	//down
	if (cellRefPossible(row + 1, col)) {
		for (int i = -1; i < 2; ++i) {
			if (!cellRefPossible(row, col + i)) {
				continue;
			}
			if (cells_[row + 1][col + i].getValue() == val) {
				++neighbours;
			}
		}
	}
	return neighbours;
}

void Game::revealNeighbours(int row, int col) {
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	std::vector<std::pair<int, int>> check_queue;
	check_queue.push_back(std::pair<int, int>(row, col));
	while (!check_queue.empty()) {
		int check_row = check_queue.back().first;
		int check_col = check_queue.back().second;
		if (cells_[check_row][check_col].getValue() == fg_value::MINE) {
			check_queue.pop_back();
			continue;
		}
		bool popped_currently_checking = false;
		for (int i = -1; i < 2; ++i) {
			for (int j = -1; j < 2; ++j) {
				//continue if we would go out of bounds
				if ((i == 0 && j == 0) || !cellRefPossible(check_row + i, check_col + j)) {
					continue;
				}
				//only queue cells that aren't mines and aren't already clicked
				if (cells_[check_row + i][check_col + j].getValue() != fg_value::MINE && !cells_[check_row + i][check_col + j].clicked()) {
					if (!popped_currently_checking) {
						check_queue.pop_back();
						printf("Popping %d, %d\n", check_row, check_col);
						popped_currently_checking = true;
					}
					//don't queue tiles with numbers in them
					if (cells_[check_row + i][check_col + j].getValue() == fg_value::NONE) {
						check_queue.push_back(std::pair<int, int>(check_row + i, check_col + j));
					}
					cells_[check_row + i][check_col + j].leftClick();
					printf("Revealing %d, %d\n", check_row + i, check_col + j);
					continue;
				}
			}
		}
		if (!popped_currently_checking) {
		check_queue.pop_back();
		}
	}
}

int Game::getRemaining() {
	int mines = getMines();
	for (int i = 0; i < getRows(); ++i) {
		for (int j = 0; j < getCols(); ++j) {
			if (cells_[i][j].flagged()) {
				//going below 0 is intentional behaviour
				--mines;
			}
		}
	}
	return mines;
}

void Game::checkLose(int row, int col) {
	if (cells_[row][col].getValue() == fg_value::MINE) {
		lose();
	}
}

void Game::lose() {
	lost_ = true;
	printf("you LOSEEEEEE :((\n");
	if (!muted_) {
		Mix_PlayChannel(-1, kaboom, 0);
	}
	for (int i = 0; i < getRows(); ++i) {
		for (int j = 0; j < getCols(); ++j) {
			if (cells_[i][j].getValue() == fg_value::MINE) {
				cells_[i][j].leftClick();
				cells_[i][j].setCellBg(bg_value::BLOWN_UP);
			}
			cells_[i][j].setUnclickable();
		}
	}
}

void Game::checkWin() {
	int remaining = 0;
	for (int i = 0; i < getRows(); ++i) {
		for (int j = 0; j < getCols(); ++j) {
			if (!cells_[i][j].clicked()) {
				if (++remaining > getMines()) {
					return;
				}
			}
		}
	}
	if (remaining == getMines() && !lost_) {
		win();
	}
}

bool Game::getWin() {
	return won_;
}

//void Game::setWin(bool win) {
//	won_ = win;
//}

void Game::win() {
	won_ = true;
	printf("YOU WINNNNNNNNNNNNNNNNNNNNNN\n");
	if (!muted_) {
		Mix_PlayChannel(-1, hellyeah, 0);
	}
	for (int i = 0; i < getRows(); ++i) {
		for (int j = 0; j < getCols(); ++j) {
			if (!cells_[i][j].clicked()) {
				cells_[i][j].setCellValue(fg_value::FLAG);
			}
		}
	}
}

void Game::checkCellClick(Sint32 x, Sint32 y, bool right_mouse) {
	for (int row = 0; row < getRows(); ++row){
		for (int col = 0; col < getCols(); ++col){
			if (cells_[row][col].getPos().x < x && cells_[row][col].getPos().x + 60.0f * cell_scale > x) {
				if (cells_[row][col].getPos().y < y && cells_[row][col].getPos().y + 60.0f * cell_scale > y) {
					if (right_mouse && cells_[row][col].getClickable()) {
						cells_[row][col].rightClick();
					} else if (!cells_[row][col].fgShown() && cells_[row][col].getClickable() && !getWin()) {
						if (!muted_) {
							Mix_PlayChannel(-1, click, 0);
						}
						cells_[row][col].leftClick();
						revealNeighbours(row, col);
						checkLose(row, col);
						checkWin();
					}
				}
			}
		}
	}
}

Cell& Game::cell(int i, int j) {
	return cells_[i][j];
}

void Game::renderBoard() {
	for (int i = 0; i < getRows(); ++i) {
		for (int j = 0; j < getCols(); ++j) {
			window.render(cell(i, j).renderBgRectInfo(), cell(i, j).getBgTex());
			if (cell(i, j).fgShown() || won_) {
				window.render(cell(i, j).renderFgRectInfo(), cell(i, j).getFgTex());
			}
		}
	}
}

void Game::renderButtons() {

}