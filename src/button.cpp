#include <SDL.h>
#include "Button.hpp"
#include "Math.hpp"

Button::Button(Vector2f pos, SDL_Rect bg_frame, SDL_Rect fg_frame, SDL_Texture* bg, SDL_Texture* fg, Game& game)
: Entity(pos, bg_frame, fg_frame, bg, fg), game_(game){
}

void Button::setGameReference(Game& game) {
	game_ = game;
}

//void Button::setFuncPointer(void (Game::*func_pointer)()) {
//	func_pointer_ = func_pointer;
//}

void Button::leftClick() {

}

void Button::rightClick() {

}