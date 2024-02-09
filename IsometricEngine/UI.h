#pragma once
#include <glm\glm.hpp>
#include "texture.h"
#include "SpriteBatch.h"
#include "actor.h"
#include "Mouse_Info.h"
#include "textrenderer.h"


class UI {
public:
	glm::vec2 pos{}, offset{};
	glm::vec4 col = glm::vec4(1);
	double scale = 3;
	bool show = true;
	glm::vec2 centeredPos()
	{
		auto p = pos;
		p.x -= m_chipset.Width / 2;
		p.y -= m_chipset.Height / 2;
		return p;
	}

	
	Texture2D m_chipset;
	void StickTo(actor * x);
	void setPos(float x, float y);
	virtual void  Draw(SpriteBatch& renderer, bool selected);	 
};