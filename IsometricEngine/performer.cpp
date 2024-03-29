#pragma once
#include "performer.h"
#include "Grid.h"
#include <algorithm>

void performer::Draw(SpriteBatch& renderer, bool selected) {

	actor::Draw(renderer, selected);
}
void performer::update(double dt) {
	for (size_t i = 0; i < Effects.size(); i++)
		Effects[i]->update(this, dt);

	if (isOnGround)	time_On_Ground += dt;
	else time_On_Ground = 0;

	jump_Timer += dt;
	if (NRJ < 0)NRJ = 0; if (NRJ > MaxNRJ)NRJ = MaxNRJ;
	if (HP < 0)HP = 0;  if (HP > Max_HP)HP = Max_HP;
	animate(dt);
	actor::update(dt);
}

void performer::update(Grid* g, double dt) {
	animate(dt);
	actor::update(dt);
}
void performer::onSide(actor* a)
{
	item* w = dynamic_cast<item*> (a);
	if (!w)return;

	printf(w->m_entityName.c_str());
	printf(" is in the pocket :smirk:\n");
	w->owner = a;
	w->CullByProximity = false;
	w->renderMe = false;
	w->collideWithMe = false;
	w->isAcollidee = false;
	Inventory.push_back(w);



}
void performer::Drop(item* w)
{
	Inventory.erase(std::remove(Inventory.begin(), Inventory.end(), w), Inventory.end());
}


actor::m_direction performer::getDirection()
{
	if (Sight.x == 1 && Sight.y == 0)
		return m_direction::NORTH;
	if (Sight.x == -1 && Sight.y == 0)
		return m_direction::SOUTH;
	if (Sight.x == -.5 && Sight.y == .5)
		return m_direction::DOWN;
	if (Sight.x == .5 && Sight.y == -.5)
		return m_direction::UP;
	if (Sight.x == .5 && Sight.y == .5)
		return m_direction::RIGHT;
	if (Sight.x == -.5 && Sight.y == -.5)
		return m_direction::LEFT;
	if (Sight.x == 0 && Sight.y == 1)
		return m_direction::EAST;
	if (Sight.x == 0 && Sight.y == -1)
		return m_direction::WEST;
	return Last_Direction;

}
//TODO, USELESS
void performer::setInputDir(glm::vec2 v)
{
	input_Dir = v;
}
void performer::animate(double dt)
{
	if (!animated || Animations.size() <= 0)return;
	if (frameRate < 0)frameRate = 1;

	float f = 0.07f / (frameRate);

	timer += dt;
	if (timer > f) {
		timer = 0;
		m_chipset = Animations[cur_Animation_ID].currentFrame();
	}
}


bool performer::addAnimation(animation a)
{
	Animations.push_back(a);
	return false;
}
//Change the animation. Return TRUE if animation has changed.
bool performer::ChangeAnimation(int x)
{
	this->cur_Animation_ID = x;
	Animations[cur_Animation_ID].reset_current_Frame();
	return true;
}
actor::m_direction testDir;


void performer::Move(glm::vec2 v, double dt)
{
	Sight.x = (v.x - v.y) / 2;
	Sight.y = (v.x + v.y) / 2;

	bool isZero = Sight.y == 0 && Sight.x == 0;
	m_direction dir = getDirection();
	vel += glm::vec3(v * speed, 0);

	ChangeAnimation(0);

	if (Last_Direction == m_direction::NORTH ||
		Last_Direction == m_direction::UP ||
		Last_Direction == m_direction::WEST ||
		Last_Direction == m_direction::LEFT)
	{
		cur_Animation_ID = 2;
	}

	if (!isZero) {
		if (dir == m_direction::NORTH || dir == m_direction::UP) {

			FlipX = true;
			cur_Animation_ID = 3;
		}
		if (dir == m_direction::WEST || dir == m_direction::LEFT) {

			FlipX = false;
			cur_Animation_ID = 3;
		}
		if (dir == m_direction::EAST || dir == m_direction::RIGHT) {
			FlipX = false;
			cur_Animation_ID = 1;
		}
		if (dir == m_direction::SOUTH || dir == m_direction::DOWN) {
			FlipX = false;
			if (dir == m_direction::SOUTH)FlipX = true;
			cur_Animation_ID = 1;
		}
	}
	if (!isOnGround) {
		cur_Animation_ID = 5;
		if (dir == m_direction::NORTH || dir == m_direction::UP || dir == m_direction::WEST || dir == m_direction::LEFT)
			cur_Animation_ID = 4;
	}

	Last_Direction = dir;
	testDir = dir;
}

void performer::Jump(double dt)
{
	if (m_Zlevel < -15) vel.z += 60;
	if (!isOnGround || NRJ == 0 || jump_Timer < jump_Delay
		|| time_On_Ground < .006) return;
	jump_Timer = 0;
	NRJ--;
	vel.z += 23;
}

