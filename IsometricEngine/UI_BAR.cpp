#include "UI_BAR.h"
#include "UI_BOX.h"

void UI_BAR::resize(float w)
{
	ui_ratio = w;
	if (ui_ratio > 1)ui_ratio = 1;
	if (ui_ratio < 0)ui_ratio = 0;
}



void UI_BAR::Draw(SpriteBatch& renderer, bool selected)
{

	if (ui_ratio < 0)ui_ratio = 0;
	if (!show)return;


	glm::vec2 p = this->pos;

	float zdepth = 9999.0f;
	glm::vec4 identity = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	double sTa = p.x - (Back.Width * scale) / 2 + Start.Width * scale;
	double si = (((Back.Width - Mid.Width + 1) * ui_ratio * scale)) - (End.Width + Start.Width) * scale;
	if (si < 0)si = 0;
	double start = sTa + Start.Width * scale / 2 + si / 2;
	double end = start + si - si / 2;

	if (&Back) {
		renderer.draw(glm::vec4(p.x, p.y,
			Back.Width * scale, Back.Height * scale),
			identity,
			Back.ID, zdepth, col);
	}


	renderer.draw(glm::vec4(sTa, p.y,
		Start.Width * scale, Start.Height * scale),
		identity,
		Start.ID, zdepth, col);


	if (si > 0) {

		renderer.draw(glm::vec4(start, p.y,
			si, Mid.Height * scale),
			identity,
			Mid.ID, zdepth, col);

	}

	renderer.draw(glm::vec4(end, p.y,
		End.Width * scale,
		End.Height * scale),
		identity,
		End.ID, 9999.0f, col);

}
