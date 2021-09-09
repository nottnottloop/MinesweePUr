#pragma once
#include "RenderWindow.hpp"

//gameplay variables
constexpr int NUM_MINES = 10;

//system variables
constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

constexpr float CELL_SCALE = 0.75f;
constexpr float CENTER_X = (SCREEN_WIDTH / 2) - 64.0f * CELL_SCALE * 4;
constexpr float CENTER_Y = (SCREEN_HEIGHT / 2) - 64.0f * CELL_SCALE * 4;

extern RenderWindow window;
extern SDL_Texture* bg;
extern SDL_Texture* fg;

enum class fg_value {
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	FLAG,
	MINE,
	NONE
};

enum class bg_value {
	NOT_CLICKED,
	CLICKED
};