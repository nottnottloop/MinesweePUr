#pragma once
#include <SDL.h>
#include "Entity.hpp"
#include "Math.hpp"
#include "Constants.hpp"

class Cell : public Entity {
public:
	Cell(Vector2f pos, SDL_Texture* tex, SDL_Rect frame, SDL_Texture* fg_tex);
	void changeFg(fg);
private:
	SDL_Texture* fg_tex_;
	SDL_Rect fg_frame_;
};