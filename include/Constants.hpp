#pragma once
#define CLEAR_COLOR 12, 67, 114

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

constexpr int CLEAR_R = 12;
constexpr int CLEAR_G = 67;
constexpr int CLEAR_B = 114;
constexpr int CLEAR_A = 0xFF;

constexpr float CELL_SCALE = 0.8f;
constexpr float CENTER_X = (SCREEN_WIDTH / 2) - 64.0f * CELL_SCALE * 4;
constexpr float CENTER_Y = (SCREEN_HEIGHT / 2) - 64.0f * CELL_SCALE * 4;

extern SDL_Texture* bg;
extern SDL_Texture* fg;

enum class value {
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