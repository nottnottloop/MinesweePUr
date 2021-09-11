#pragma once
#include <SDL.h>
#include "Entity.hpp"
#include "Math.hpp"
#include "Constants.hpp"

class Cell : public Entity {
public:
	//Cell(Vector2f pos, SDL_Rect bg_frame, SDL_Rect fg_frame, SDL_Texture* bg, SDL_Texture* fg) : Entity(pos, bg_frame, fg_frame, bg, fg);
	Cell(Vector2f pos, Vector2f offset, SDL_Rect bg_frame, SDL_Rect fg_frame, SDL_Texture* bg, SDL_Texture* fg);
	void setCellValue(fg_value val);
	void setCellFg(fg_value val);
	void setCellBg(bg_value val);
	void setFlagState();
	fg_value getValue();
	void leftClick();
	void rightClick();
	bool fgShown();
	bool clicked();
	bool flagged();
private:
	fg_value cell_value_;
	bool clicked_;
	bool flagged_;
};