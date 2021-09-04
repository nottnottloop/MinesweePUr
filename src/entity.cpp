#include "Entity.hpp"
#include <SDL.h>
#include <SDL_image.h>

Entity::Entity(Vector2f pos, SDL_Texture* tex)
:pos_(pos), tex_(tex), currentFrame_({0, 0, 32, 32}) {
	currentFrame_.x = 0;
	currentFrame_.y = 0;
	currentFrame_.w = 32;
	currentFrame_.h = 32;
}

const Vector2f& Entity::getPos() const {
	return pos_;
}

const SDL_Texture* Entity::getTex() const {
	return tex_;
}

const SDL_Rect Entity::getCurrentFrame() const {
	return currentFrame_;
}