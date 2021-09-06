#include "Cell.hpp"
#include "Constants.hpp"

void Cell::changeValue(value foreground) {
	cell_value_ = foreground;
}

value Cell::getValue() {
	return cell_value_;
}