#include "cell.hpp"

Cell::Cell(Vector2f pos, SDL_Texture* tex, SDL_Rect frame, SDL_Texture* fg_tex)
:Entity(pos, tex, frame), fg_tex_(fg_tex) {

}