#include "Cell.hpp"
#include "Constants.hpp"

Cell::Cell(Vector2f pos, SDL_Texture* tex, SDL_Rect frame)
:Entity(pos, tex, frame) {

}

void Cell::changeValue(value foreground) {
	cell_value_ = foreground;
}