#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <tuple>

#include <Math.hpp>

class Entity {
public:
	Entity(Vector2f pos, SDL_Rect frame, SDL_Texture* bg, SDL_Texture* fg);
	Vector2f getPos() const;
	SDL_Texture* getTex() const;
	void setTex(SDL_Texture* tex);
	SDL_Rect getCurrentFrame() const;
	void setCurrentFrame(SDL_Rect rect);
	void setScale(double scale);
	double getScale();
	std::tuple<SDL_Rect, SDL_Rect> renderRectInfo();
protected:
	Vector2f pos_;
	SDL_Texture* tex_;
	SDL_Rect current_frame_;
	SDL_Texture* fg_tex_;
	SDL_Rect fg_frame_;
	double scale_;
};