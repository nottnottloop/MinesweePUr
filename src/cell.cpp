#include "Cell.hpp"
#include "Constants.hpp"

void Cell::changeCellValue(fg_value val) {
	cell_value_ = val;
	changeFg(val);
}

void Cell::changeFg(fg_value val) {
	if (val != fg_value::NONE) {
		int num = static_cast<int>(val);
		fg_frame_.x = num * 64;
	} else {
		fg_frame_.x = -64;
	}
}

void Cell::changeFlagState() {
	flagged_ = !flagged_;
	if (flagged_) {
		changeFg(fg_value::FLAG);
	} else  {
		changeFg(fg_value::NONE);
	}
}

fg_value Cell::getValue() {
	return cell_value_;
}

bool Cell::shown() {
	return true;
	if (clicked_ || flagged_) {
		return true;
	} else {
		return false;
	}
}