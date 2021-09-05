#include "Entity.hpp"
#include <SDL.h>
#include <SDL_image.h>

Entity::Entity(Vector2f pos, SDL_Texture* tex, SDL_Rect frame)
:pos_(pos), tex_(tex), currentFrame_(frame) {

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