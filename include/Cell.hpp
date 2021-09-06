#pragma once
#include <SDL.h>
#include "Entity.hpp"
#include "Math.hpp"
#include "Constants.hpp"

class Cell : public Entity {
public:
	Cell(Vector2f pos, SDL_Rect frame, SDL_Texture* bg, SDL_Texture* fg) : Entity(pos, frame, bg, fg) {};
	void changeValue(value foreground);
	value getValue();
private:
	value cell_value_;
	bool clicked_;
	bool flagged_;
};