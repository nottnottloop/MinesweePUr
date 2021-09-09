#pragma once
#include "RenderWindow.hpp"

extern float cell_scale;
constexpr int BEGINNER_OFFSET = 50;
constexpr int MEDIUM_OFFSET = 60;
constexpr int EXPERT_OFFSET = 50;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

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
	CLICKED,
	BLOWN_UP
};