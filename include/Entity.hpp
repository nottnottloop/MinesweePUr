#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <tuple>

#include <Math.hpp>

class Entity {
public:
	Entity(Vector2f pos, Vector2f offset, SDL_Rect bg_frame, SDL_Rect fg_frame, SDL_Texture* bg, SDL_Texture* fg);
	Vector2f getPos() const;
	void setPos(Vector2f pos);
	Vector2f getOffset() const;
  void setOffset(Vector2f offset);

	SDL_Texture* getBgTex() const;
	void setBgTex(SDL_Texture* tex);
	SDL_Texture* getFgTex() const;
	void setFgTex(SDL_Texture* tex);

	bool getVisible();
	void setVisible();
	void setInvisible();
	void toggleVisible();

	bool getClickable();
	void setClickable();
	void setUnclickable();
	void toggleClickable();

	SDL_Rect getBgFrame() const;
	void setBgFrame(SDL_Rect rect);
	SDL_Rect getFgFrame() const;
	void setFgFrame(SDL_Rect rect);

	void setScale(double scale);
	double getScale();
	std::tuple<SDL_Rect, SDL_Rect> renderBgRectInfo();
	std::tuple<SDL_Rect, SDL_Rect> renderFgRectInfo();
	//virtual void leftClick() = 0;
	//virtual void rightClick() = 0;
protected:
	Vector2f pos_;
	Vector2f offset_;
	SDL_Texture* bg_tex_;
	SDL_Rect bg_frame_;
	SDL_Texture* fg_tex_;
	SDL_Rect fg_frame_;
	double scale_;
	bool visible_;
	bool clickable_;
};