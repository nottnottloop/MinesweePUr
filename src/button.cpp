#include <SDL.h>
#include "Button.hpp"
#include "Math.hpp"

Button::Button(Vector2f pos, Vector2f offset, SDL_Rect bg_frame, SDL_Rect fg_frame, SDL_Texture* bg, SDL_Texture* fg, Game& game, void (Game::*func_pointer)())
: Entity(pos, offset, bg_frame, fg_frame, bg, fg), game_(game), func_pointer_(func_pointer) {
}

void Button::setGameReference(Game& game) {
	game_ = game;
}

void Button::setFuncPointer(void (Game::*func_pointer)()) {
	func_pointer_ = func_pointer;
}

void Button::leftClick() {
	if (func_pointer_ != nullptr) {
		(game_.*func_pointer_)();
	}
}

void Button::rightClick() {
	if (func_pointer_ != nullptr) {
		(game_.*func_pointer_)();
	}
}