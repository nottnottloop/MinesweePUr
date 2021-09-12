#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Entity.hpp"

class Text : public Entity {
public:
	Text(Vector2f pos, Vector2f offset, int size);
	void loadFontTexture(SDL_Color color, const char* text);
	void openFont(const char* file_path, int size);
	SDL_Rect renderTextInfo();
	SDL_Rect renderCenteredTextInfo();
	void setSize(int size);
	int getSize();
private:
	TTF_Font* font_;
	int size_;
};