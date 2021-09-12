#include <SDL.h>
#include <SDL_ttf.h>
#include "Text.hpp"
#include "Math.hpp"
#include "Constants.hpp"

Text::Text(Vector2f pos, Vector2f offset, int size)
: Entity(pos, offset, {0, 0, 0, 0}, {0, 0, 0, 0}, nullptr, nullptr), size_(size) {
}

void Text::loadFontTexture(SDL_Color color, const char* text) {
	SDL_DestroyTexture(fg_tex_);
	SDL_Surface* surface = TTF_RenderText_Solid(font_, text, color);
	fg_tex_ = SDL_CreateTextureFromSurface(window.renderer_, surface);
	SDL_FreeSurface(surface);
}

SDL_Rect Text::renderTextInfo() {
	int tex_w = 0;
	int tex_h = 0;
	SDL_QueryTexture(fg_tex_, nullptr, nullptr, &tex_w, &tex_h);
	SDL_Rect dst_rect = { getPos().x, getPos().y, tex_w, tex_h };
	return dst_rect;
}

SDL_Rect Text::renderCenteredTextInfo() {
	int tex_w = 0;
	int tex_h = 0;
	SDL_QueryTexture(fg_tex_, nullptr, nullptr, &tex_w, &tex_h);
	SDL_Rect dst_rect = { getPos().x - tex_w, getPos().y, tex_w, tex_h };
	return dst_rect;
}

void Text::openFont(const char* file_path, int size) {
	font_ = TTF_OpenFont(file_path, size);
}

void Text::setSize(int size) {
	size_ = size;
}

int Text::getSize() {
	return size_;
}