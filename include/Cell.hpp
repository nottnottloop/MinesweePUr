#pragma once
#include <SDL.h>
#include "Entity.hpp"
#include "Math.hpp"

class Cell : public Entity {
public:
	Cell(Vector2f pos, SDL_Texture* tex, SDL_Rect frame);

};