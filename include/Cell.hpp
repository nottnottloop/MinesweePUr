#pragma once
#include <SDL.h>
#include "Entity.hpp"
#include "Math.hpp"
#include "Constants.hpp"

class Cell : public Entity {
public:
	Cell(Vector2f pos, SDL_Texture* tex, SDL_Rect frame, SDL_Texture* fg_tex);
	void changeValue(value foreground);
private:
	SDL_Texture* fg_tex_;
	SDL_Rect fg_frame_;
	value cell_value_;
	bool clicked_;
	bool flagged_;
};