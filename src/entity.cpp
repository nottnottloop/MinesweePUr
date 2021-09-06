#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"

Entity::Entity(Vector2f pos, SDL_Texture* tex, SDL_Rect frame)
:pos_(pos), tex_(tex), current_frame_(frame) {

}

Vector2f Entity::getPos() const {
	return pos_;
}

SDL_Texture* Entity::getTex() const {
	return tex_;
}

void Entity::setTex(SDL_Texture* tex) {
	tex_ = tex;
}

SDL_Rect Entity::getCurrentFrame() const {
	return current_frame_;
}