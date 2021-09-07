#pragma once
#include <SDL.h>
#include "Entity.hpp"
#include "Math.hpp"
#include "Constants.hpp"

class Cell : public Entity {
public:
	Cell(Vector2f pos, SDL_Rect bg_frame, SDL_Rect fg_frame, SDL_Texture* bg, SDL_Texture* fg) : Entity(pos, bg_frame, fg_frame, bg, fg) {};
	void changeCellValue(value val);
	void changeFg(value val);
	void changeFlagState();
	value getValue();
	bool shown();
private:
	value cell_value_;
	bool clicked_;
	bool flagged_;
};