#include <SDL.h>
#include <SDL_ttf.h>
#include "Text.hpp"
#include "Math.hpp"
#include "Constants.hpp"

Text::Text(Vector2f pos, Vector2f offset)
: Entity(pos, offset, {0, 0, 0, 0}, {0, 0, 0, 0}, nullptr, nullptr) {
}

void Text::loadFontTexture(const char* file_path, int size, SDL_Color color, const char* text) {
	TTF_Font * font = TTF_OpenFont(file_path, 25);
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
	fg_tex_ = SDL_CreateTextureFromSurface(window.renderer_, surface);
	SDL_FreeSurface(surface);
}

SDL_Rect Text::renderTextInfo() {
	int tex_w = 0;
	int tex_h = 0;
	SDL_QueryTexture(fg_tex_, NULL, NULL, &tex_w, &tex_h);
	SDL_Rect dst_rect = { getPos().x, getPos().y, tex_w, tex_h };
	return dst_rect;
}