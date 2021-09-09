#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <tuple>
#include "RenderWindow.hpp"
#include "Constants.hpp"
#include "Text.hpp"

RenderWindow::RenderWindow(const char* p_title, const int p_w, const int p_h)
	:window_(NULL), renderer_(NULL) {
	window_ = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_HIDDEN);

	if (window_ == nullptr) {
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer_ == nullptr) {
		std::cout << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
	}
}

SDL_Texture* RenderWindow::loadTexture(const char* file_path) {
	SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(renderer_, file_path);

	if (texture == nullptr)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::cleanUp() {
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
}

void RenderWindow::clear() {
	SDL_SetRenderDrawColor(renderer_, 12, 67, 114, 0xFF);        
	SDL_RenderClear(renderer_);
}

void RenderWindow::clear(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(renderer_, r, g, b, a);        
	SDL_RenderClear(renderer_);
}

void RenderWindow::render(Text text) const {
	SDL_RenderCopy(renderer_, text.getFgTex(), nullptr, &text.renderTextInfo());
}

void RenderWindow::render(std::tuple<SDL_Rect, SDL_Rect> rects, SDL_Texture* tex) const {
	SDL_RenderCopy(renderer_, tex, &std::get<0>(rects), &std::get<1>(rects));
}

void RenderWindow::display() const {
	SDL_RenderPresent(renderer_);
}

void RenderWindow::showWindow() {
	SDL_ShowWindow(window_);
}

void RenderWindow::renderRect(int r, int g, int b) {
	SDL_Rect rect = { SCREEN_WIDTH / 12, SCREEN_HEIGHT / 10, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
	SDL_SetRenderDrawColor( renderer_, r, g, b, 0xFF );        
	SDL_RenderDrawRect( renderer_, &rect );
}