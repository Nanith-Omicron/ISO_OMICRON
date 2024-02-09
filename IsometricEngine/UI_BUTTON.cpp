#include "UI_BUTTON.h"
//TO DO, function are better
bool UI_BUTTON::Update(Mouse_info m, bool x)
{
	bool UseClick = state == UI_BUTTON_STATE::CLICKED;
	state = UI_BUTTON_STATE::NORMAL;
	if (x)return false;
	ui_size_y = norm.tr.Height * scale;
	if (!onlyCenter)ui_size_y = norm.tr.Height * scale * sy - (norm.tr.Height + norm.tl.Height) * scale;
	ui_size_x = (norm.tm.Width * sx) * scale - (norm.tr.Width + norm.tl.Width) * scale;


	if (m.rawX > pos.x && m.rawX < pos.x + ui_size_x)
		if (m.rawY > pos.y - ui_size_y / 2 && m.rawY < pos.y + ui_size_y / 2) {

			if (m.buttons[0]) {
				state = UI_BUTTON_STATE::CLICKED;
				if (!UseClick && onClick != NULL) {
					onClick();

					return true;
				}
				if (!UseClick && function != NULL) {
					function();
					return true;
				}
			}
			else if (m.buttons[1])state = UI_BUTTON_STATE::RIGHT_CLICKED;
			else state = UI_BUTTON_STATE::HOVER;


		}
	return state != UI_BUTTON_STATE::NORMAL;
}

void UI_BUTTON::Draw(SpriteBatch& renderer, bool selected, _box* box)
{
	_box* lol = &norm;


	switch (state)
	{
	case UI_BUTTON_STATE::NORMAL:
		lol = &norm;
		lol->empt = false;

		break;
	case UI_BUTTON_STATE::HOVER:
		lol = &hov;
		lol->empt = false;

		break;
	case UI_BUTTON_STATE::CLICKED:
		lol = &click;
		lol->empt = false;
		break;
	case UI_BUTTON_STATE::RIGHT_CLICKED:
		break;
	case UI_BUTTON_STATE::DRAGGED:
		break;
	default:
		lol = &norm;
		lol->empt = false;

		break;
	}
	UI_BOX::Draw(renderer, selected, lol);

}


