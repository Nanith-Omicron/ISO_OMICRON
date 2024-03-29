#include "UI.h"

void UI::StickTo(actor * x)
{
	pos = x->pos + offset;
}

void UI::setPos(double x, double y)
{
	pos =  glm::vec2(x, y);
}

void UI::Draw(SpriteBatch& renderer, bool selected)
{
	if (!show)return; 
 	glm::vec2 p = this->pos;
	float qw = 1;
 
		renderer.draw(glm::vec4(p.x, p.y,
			m_chipset.Width * scale, m_chipset.Height*scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
			m_chipset.ID, 9999.0f, col);
}
 	
 