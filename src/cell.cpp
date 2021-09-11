#include "Cell.hpp"
#include "Constants.hpp"

Cell::Cell(Vector2f pos, Vector2f offset, SDL_Rect bg_frame, SDL_Rect fg_frame, SDL_Texture* bg, SDL_Texture* fg)
: Entity(pos, offset, bg_frame, fg_frame, bg, fg) {
	setScale(cell_scale);
	setCellValue(fg_value::NONE);
	clicked_ = false;
	flagged_ = false;
}

void Cell::setCellValue(fg_value val) {
	cell_value_ = val;
	setCellFg(val);
}

void Cell::setCellFg(fg_value val) {
	if (val != fg_value::NONE) {
		int num = static_cast<int>(val);
		fg_frame_.x = num * 60;
	} else {
		fg_frame_.x = -60;
	}
}

void Cell::setCellBg(bg_value val) {
	int num = static_cast<int>(val);
	bg_frame_.x = num * 60;
}

void Cell::setFlagState() {
	flagged_ = !flagged_;
	if (flagged_) {
		setCellFg(fg_value::FLAG);
	} else  {
		setCellFg(fg_value::NONE);
	}
}

fg_value Cell::getValue() {
	return cell_value_;
}

void Cell::leftClick() {
	if (!flagged_ && clickable_) {
		clicked_ = true;
		setCellBg(bg_value::CLICKED);
	}
}

void Cell::rightClick() {
	if (!clicked_) {
		if (!flagged_) {
			flagged_ = true;
			setCellFg(fg_value::FLAG);
		} else {
			flagged_ = false;
			setCellFg(cell_value_);
		}
	}
}

bool Cell::fgShown() {
	//DEBUG to show all cells
	//return false;
	if (clicked_ || flagged_) {
		return true;
	} else {
		return false;
	}
}

bool Cell::clicked() {
	return clicked_;
}

bool Cell::flagged() {
	return flagged_;
}