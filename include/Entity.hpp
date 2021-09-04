#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include <Math.hpp>

class Entity {
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex);
	const Vector2f& getPos() const;
	const SDL_Texture* getTex() const;
	const SDL_Rect getCurrentFrame() const;
private:
	Vector2f pos_;
	SDL_Texture* tex_;
	SDL_Rect currentFrame_;
};