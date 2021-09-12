#include <SDL.h>
#include <SDL_image.h>
#include <tuple>
#include "Entity.hpp"

Entity::Entity(Vector2f pos, Vector2f offset, SDL_Rect bg_frame, SDL_Rect fg_frame, SDL_Texture* bg, SDL_Texture* fg)
:pos_(pos), offset_(offset), bg_frame_(bg_frame), fg_frame_(fg_frame), bg_tex_(bg), fg_tex_(fg), scale_(1), clickable_(true), visible_(true) {

}

Vector2f Entity::getPos() const {
	return pos_ + offset_;
}

void Entity::setPos(Vector2f pos) {
	pos_ = pos;
}

Vector2f Entity::getOffset() const {
	return offset_;
}

void Entity::setOffset(Vector2f offset) {
	offset_ = offset;
}

bool Entity::getVisible() {
	return visible_;
}

void Entity::setVisible() {
	visible_ = true;
}

void Entity::setInvisible() {
	visible_ = false;
}

void Entity::toggleVisible() {
	visible_ = !visible_;
}

bool Entity::getClickable() {
	return clickable_;
}

void Entity::setClickable() {
	clickable_ = true;
}

void Entity::setUnclickable() {
	clickable_ = false;
}

void Entity::toggleClickable() {
	clickable_ = !visible_;
}

SDL_Texture* Entity::getBgTex() const {
	if (visible_) {
		return bg_tex_;
	}
	return nullptr;
}

void Entity::setBgTex(SDL_Texture* tex) {
	bg_tex_ = tex;
}

SDL_Texture* Entity::getFgTex() const {
	if (visible_) {
		return fg_tex_;
	}
	return nullptr;
}

void Entity::setFgTex(SDL_Texture* tex) {
	fg_tex_ = tex;
}

SDL_Rect Entity::getBgFrame() const {
	return bg_frame_;
}

void Entity::setBgFrame(SDL_Rect rect) {
	bg_frame_.x = rect.x;
	bg_frame_.y = rect.y;
	bg_frame_.w = rect.w;
	bg_frame_.h = rect.h;
}

SDL_Rect Entity::getFgFrame() const {
	return fg_frame_;
}

void Entity::setFgFrame(SDL_Rect rect) {
	fg_frame_.x = rect.x;
	fg_frame_.y = rect.y;
	fg_frame_.w = rect.w;
	fg_frame_.h = rect.h;
}

void Entity::setScale(double scale) {
	scale_ = scale;
}

double Entity::getScale() {
	return scale_;
}

std::tuple<SDL_Rect, SDL_Rect> Entity::renderBgRectInfo() {
	SDL_Rect src = getBgFrame(); 

	SDL_Rect dst;
	dst.x = getPos().x;
	dst.y = getPos().y;
	dst.w = getBgFrame().w * getScale();
	dst.h = getBgFrame().h * getScale();
	return {src, dst};
}

std::tuple<SDL_Rect, SDL_Rect> Entity::renderFgRectInfo() {
	SDL_Rect src = getFgFrame(); 

	SDL_Rect dst;
	dst.x = getPos().x;
	dst.y = getPos().y;
	dst.w = getBgFrame().w * getScale();
	dst.h = getBgFrame().h * getScale();
	return {src, dst};
}