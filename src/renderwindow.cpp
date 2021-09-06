#include "RenderWindow.hpp"
#include "Constants.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

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
	SDL_DestroyWindow(window_);
}

void RenderWindow::clear() {
	SDL_SetRenderDrawColor( renderer_, 0, 0, 0, 0xFF );        
	SDL_RenderClear(renderer_);
}

void RenderWindow::render(const Entity& entity, double scale) const {
	SDL_Rect src; 
	src.x = entity.getCurrentFrame().x;
	src.y = entity.getCurrentFrame().y;
	src.w = entity.getCurrentFrame().w;
	src.h = entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = entity.getPos().x;
	dst.y = entity.getPos().y;
	dst.w = entity.getCurrentFrame().w * scale;
	dst.h = entity.getCurrentFrame().h * scale;

	SDL_RenderCopy(renderer_, const_cast<SDL_Texture*>(entity.getTex()), &src, &dst);
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