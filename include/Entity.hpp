#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include <Math.hpp>

class Entity {
public:
	Entity(Vector2f pos, SDL_Texture* tex, SDL_Rect frame);
	Vector2f getPos() const;
	SDL_Texture* getTex() const;
	void setTex(SDL_Texture* tex);
	SDL_Rect getCurrentFrame() const;
protected:
	Vector2f pos_;
	SDL_Texture* tex_;
	SDL_Rect current_frame_;
};