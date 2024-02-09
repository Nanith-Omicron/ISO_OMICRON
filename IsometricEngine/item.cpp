#include "item.h"
#include "performer.h"

void item::update(float dt)
{
}

void item::onSide(actor* a)
{
	if (autoPickup)
		onGet(a);
}

void item::use(actor* a)
{

}

void item::onGet(actor* a)
{
	if (!CullByProximity)return;

	//printf("Player got the %s", name);

	//a->onSide(this);



}

void item::onDrop(actor* a)
{
	owner = nullptr;
	if (a)pos = a->pos;
	renderMe = true;
	collideWithMe = true;
	CullByProximity = true;
}
bool item::CollisionWithMe(actor* a) {

	if (autoPickup && DistanceFrom(a) < pickupRange * pickupRange) {


		if (this->m_Zlevel + collisionBoundZ.x > a->m_Zlevel - a->collisionBoundZ.x
			&& this->m_Zlevel - collisionBoundZ.y < a->m_Zlevel + a->collisionBoundZ.y)
			onSide(a);
		return true;


	}
	actor::CollisionWithMe(a);


}

void item::Draw(SpriteBatch & renderer, bool selected)
{
	if (!&m_chipset || !renderMe)return;
	glm::vec3 c = this->color + this->fxColors;
	glm::vec2 p = this->pos + glm::vec2(0, sin(_internTimer) * 7.5 - 30);
	glm::vec2 s = this->size * 3.0f;
	auto uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	p.y -= (m_Zlevel / (55 / 33));

	p.y -= (m_chipset.Height);
	p.x -= 2;

	glm::vec2 spos = pos;

	spos.y -= platZ;
	//p.y -= zDepthOffset;
	double dyMiz = .7 + (platZ - m_Zlevel) * .001f;
	if (dyMiz > 1.2f)dyMiz = 1.2f;
	auto s2 = glm::vec2(100, 50);
	if (FlipX)s2.x *= -1;
	_internTimer += 0.01f;

	s.x *= m_chipset.Width;
	s.y *= m_chipset.Height;

	renderer.draw(glm::vec4(p.x, p.y,
		s.x, s.y),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		m_chipset.ID, pos.y + zDepthOffset + m_Zlevel + 210, glm::vec4(c * alpha, 1));

	renderer.draw(glm::vec4(spos.x - 2, spos.y + 2,
		s2.x * dyMiz, s2.y * dyMiz),
		uvRect,
		m_chipshadow.ID, pos.y + zDepthOffset + platZ - 10 + 210, glm::vec4(c, dyMiz));


}
