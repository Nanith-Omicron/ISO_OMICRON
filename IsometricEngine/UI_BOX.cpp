#include "UI_BOX.h"

void UI_BOX::resize(double x, double y)
{
	sx = x;
	sy = y-.5;
}


void UI_BOX::Draw(SpriteBatch& renderer, bool selected) {


	if (!show)return;
	glm::vec2 p = this->pos;
	_box box;
 
	box = internal_box;

	double sTa = p.x + box.tl.Width * scale / 2;

		
	double si = (((box.tm.Width) * sx * scale)) - (box.tr.Width + box.tl.Width) * scale;
	double xsi = (((box.m.Height) * sy * scale)) - (box.m.Height + box.tl.Height) * scale;

	double yEnd = box.tm.Height * scale / 2 + xsi / 2;
	if (si < 0)si = 0;
	double start = sTa + si / 2;
	double end = start + si / 2;


	renderer.draw(glm::vec4(p.x, p.y,
		box.tl.Width * scale, box.tl.Height * scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		box.tl.ID, 9999999999, col);
	renderer.draw(glm::vec4(start, p.y,
		si, box.tm.Height * scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		box.tm.ID, 9999999999, col);
	renderer.draw(glm::vec4(end, p.y,
		box.tr.Width * scale, box.tr.Height * scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		box.tr.ID, 9999999999, col);

	if (onlyCenter)return;
	// center
	renderer.draw(glm::vec4(p.x, p.y + yEnd,
		box.ml.Width * scale, xsi),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		box.ml.ID, 9999999999, col);

	renderer.draw(glm::vec4(start, p.y + yEnd,
		si, xsi),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		box.m.ID, 9999999999, col);

	renderer.draw(glm::vec4(end, p.y + yEnd,
		box.mr.Width * scale, xsi),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		box.mr.ID, 9999999999, col);

	//  end
	renderer.draw(glm::vec4(p.x, p.y + xsi + box.ll.Width * scale,
		box.ll.Width * scale, box.ll.Width * scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		box.ll.ID, 9999999999, col);

	renderer.draw(glm::vec4(start, p.y + xsi + box.lm.Width * scale,
		si, box.lm.Width * scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		box.lm.ID, 9999999999, col);

	renderer.draw(glm::vec4(end, p.y + xsi + box.lr.Width * scale,
		box.lr.Width * scale, box.lr.Width * scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		box.lr.ID, 9999999999, col);


}

void UI_BOX::DrawText(TextRenderer& Text)
{
	if (!hasText)return;
	Text.RenderText(TextToWrite,
		pos.x + renderedSize().x / 2 + 24 * font_size - (TextToWrite.size()) * 9 * font_size,
		pos.y - font_size * 24 / 2, font_size, glm::vec4(.8,.8,.8,.2));

}

void UI_BOX::Draw(SpriteBatch& renderer, bool selected, _box * b  ){


	if (!show)return;
	glm::vec2 p = this->pos;
	_box box;
	if (!b)
		box = internal_box;
	else
		box = *b;
		

	double sTa = p.x + box.tl.Width * scale/2;

	double si = (((box.tm.Width ) * sx * scale)) - (box.tr.Width + box.tl.Width) * scale;
	double xsi = (((box.m.Height) * sy * scale)) - (box.m.Height + box.tl.Height) * scale;
 
	double yEnd = box.tm.Height * scale / 2 + xsi / 2;
	if (si < 0)si = 0;
	double start = sTa    + si / 2;
	double end = start +  si / 2;
 

	renderer.draw(glm::vec4(p.x, p.y,
		box.tl.Width * scale, box.tl.Height * scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		box.tl.ID, 9999999999, col);
	renderer.draw(glm::vec4(start, p.y,
			si, box.tm.Height * scale),
			glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		box.tm.ID, 9999999999, col);
	renderer.draw(glm::vec4(end, p.y,
		box.tr.Width * scale, box.tr.Height * scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		box.tr.ID, 9999999999, col);

	if (onlyCenter)return;
	// center
	renderer.draw(glm::vec4(p.x, p.y + yEnd,
		 box.ml.Width * scale, xsi),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		box.ml.ID, 9999999999, col);

	renderer.draw(glm::vec4(start, p.y + yEnd,
		si, xsi),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		box.m.ID, 9999999999, col);

	renderer.draw(glm::vec4(end, p.y + yEnd,
		box.mr.Width * scale, xsi),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		box.mr.ID, 9999999999, col);

	//  end
	renderer.draw(glm::vec4(p.x, p.y + xsi + box.ll.Width * scale,
		box.ll.Width * scale, box.ll.Width* scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		box.ll.ID, 9999999999, col);

	renderer.draw(glm::vec4(start, p.y + xsi + box.lm.Width * scale,
		si, box.lm.Width* scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		box.lm.ID, 9999999999, col);

	renderer.draw(glm::vec4(end, p.y + xsi + box.lr.Width * scale,
		box.lr.Width * scale, box.lr.Width* scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		box.lr.ID, 9999999999, col);


}
