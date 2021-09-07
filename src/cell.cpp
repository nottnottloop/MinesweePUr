#include "Cell.hpp"
#include "Constants.hpp"

void Cell::changeCellValue(value val) {
	cell_value_ = val;
	changeFg(val);
}

void Cell::changeFg(value val) {
	if (val != value::NONE) {
		int num = static_cast<int>(val);
		fg_frame_.x = num * 64;
	} else {
		fg_frame_.x = -64;
	}
}

void Cell::changeFlagState() {
	flagged_ = !flagged_;
	if (flagged_) {
		changeFg(value::FLAG);
	} else  {
		changeFg(value::NONE);
	}
}

value Cell::getValue() {
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