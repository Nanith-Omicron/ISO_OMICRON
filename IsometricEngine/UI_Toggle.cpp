#include "UI_Toggle.h"

void UI_Toggle::Draw(SpriteBatch& renderer, bool selected)
{

 
	if (!show)return;
	glm::vec2 p = this->pos;

	float zdepth = 9999.0f;
	glm::vec4 identity = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	renderer.draw(glm::vec4(p.x, p.y,
		Off.Width * scale, Off.Height * scale),
		identity,
		Off.ID, zdepth, col);
	if (!isOn)return;
	renderer.draw(glm::vec4(p.x, p.y-1*scale,
		On.Width * scale, On.Height * scale),
		identity,
		On.ID, zdepth, col);
}
