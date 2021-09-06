#pragma once
#include <SDL.h>
#include "Entity.hpp"
#include "Math.hpp"
#include "Constants.hpp"

class Cell : public Entity {
public:
	Cell(Vector2f pos, SDL_Texture* tex, SDL_Rect frame);
	void changeValue(value foreground);
private:
	value cell_value_;
	bool clicked_;
	bool flagged_;
};