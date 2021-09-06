#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Entity.hpp"

class RenderWindow 
{
public:
	RenderWindow(const char* title, int w, int h);
	SDL_Texture* loadTexture(const char* file_path);
	void cleanUp();
	void clear();
	void render(const Entity& entity, double scale = 1) const;
	void display() const;
	void showWindow();
	void renderRect(int r, int g, int b);
private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;
};