#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Entity.hpp"

class Text : public Entity {
public:
	Text(Vector2f pos, Vector2f offset);
	void loadFontTexture(const char* file_path, int size, SDL_Color color, const char* text);
	SDL_Rect Text::renderTextInfo();
private:
};