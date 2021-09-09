#pragma once
#include <SDL.h>
#include "Entity.hpp"
#include "Math.hpp"
#include "Game.hpp"

class Button : public Entity {
public:
	Button(Vector2f pos, Vector2f offset, SDL_Rect bg_frame, SDL_Rect fg_frame, SDL_Texture* bg, SDL_Texture* fg, Game& game, void (Game::*func_pointer)());
	void setGameReference(Game& game);
	void setFuncPointer(void (Game::*func_pointer)());
	void leftClick();
	void rightClick();
private:
	Game& game_;
	void (Game::*func_pointer_)();
};