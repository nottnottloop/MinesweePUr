#pragma once
#include <vector>
#include <SDL_mixer.h>
#include "RenderWindow.hpp"

constexpr SDL_Color CLASSIC_BACKGROUND = {12, 67, 114};
constexpr SDL_Color NEW_BACKGROUND = {64, 114, 148};
constexpr SDL_Color RED = {255, 0, 0};
constexpr SDL_Color GREEN = {0, 255, 0};
constexpr SDL_Color BLUE = {0, 0, 255};
constexpr SDL_Color CYAN = {0, 255, 255};
constexpr SDL_Color PEACH = {255, 229, 180};
constexpr SDL_Color PURPLE = {128, 0, 128};
constexpr SDL_Color ORANGE_RED = {255, 69, 0};
constexpr SDL_Color WHITE = {255, 255, 255};
constexpr SDL_Color BLACK = {0, 0, 0};

extern float cell_scale;
constexpr int BEGINNER_OFFSET = 50;
constexpr int MEDIUM_OFFSET = 60;
constexpr int EXPERT_OFFSET = 20;

constexpr char* FONT_LOCATION = "res/fixedsys.ttf";

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern Mix_Chunk* click;
extern Mix_Chunk* kaboom;
extern Mix_Chunk* hellyeah;

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