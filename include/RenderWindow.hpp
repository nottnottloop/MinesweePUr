#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <tuple>

#include "Entity.hpp"

class RenderWindow 
{
public:
	RenderWindow(const char* title, int w, int h);
	SDL_Texture* loadTexture(const char* file_path);
	void cleanUp();
	void clear(int r = 0, int g = 0, int b = 0, int a = 0xFF);
	void render(std::tuple<SDL_Rect, SDL_Rect> rects, double scale, SDL_Texture* bg_tex, SDL_Texture* fg_tex) const;
	void display() const;
	void showWindow();
	void renderRect(int r, int g, int b);
private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;
};