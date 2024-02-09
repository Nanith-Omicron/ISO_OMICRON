#pragma once
#include "actor.h"
#include "rect.h"

 
float actor::DistanceFrom(actor* a) {
	auto w = a->localPos() - localPos();
	return w.x* w.x + w.y * w.y;
	// slow return sqrt((w.x * w.x + w.y * w.y));
}

float actor::DistanceFrom(glm::vec2 pos) {
	auto w = pos - localPos();
	return w.x* w.x + w.y * w.y;
	// slow return sqrt((w.x * w.x + w.y * w.y));
}
void actor::onTop(actor* a) {


}
void actor::onSide(actor* a) {


}
void actor::onBottom(actor* a) {

}
void actor::preCollision(actor* a) {
	if (!collideWithMe)return;
	  if (a == this)return;
	CollisionWithMe(a); 
	 
}
void  actor::activeActor(bool t) {
	if (!CullByProximity)return;
	collideWithMe = t;
	renderMe = t;
	physicsMe = t;
}
//TODO change to Radius Type collision
bool actor::CollisionWithMe(actor * a) {

	 
	float localx = this->localPos().x - this->collisionBoundXY.x/2;
	float localy = this->localPos().y - this->collisionBoundXY.y / 2;
	glm::vec2 act_pos = a->localPos() - this->collisionBoundXY/2.0f;
	float act_z = a->m_Zlevel;
	glm::vec2 act_bound = a->collisionBoundXY;
	bool grd = false;
	//To fired off events. We do not take the Actual size in count. 
	if (act_pos.x > localx - 1 && act_pos.x < localx + 1)
		if (act_pos.y > localy - 1 && act_pos.y < localy + 1)
			//40
			if (this->m_Zlevel > act_z && this->m_Zlevel < act_z + 30) {
				onTop(a);
				if (this->m_Zlevel > act_z && this->m_Zlevel < act_z + 30)
					if (a->vel.z < 0 || (a->m_Zlevel + a->vel.z) < m_Zlevel)a->vel.z = 0;

				if ((act_z + a->vel.z) < m_Zlevel)act_z = 0;

				grd = true;

				//if(!a->isOnGround && a->vel.z < 1)a->vel.z = 15;




			}

	//Collision Side
	if (act_pos.x + act_bound.x > localx - this->collisionBoundXY.x &&
		act_pos.x - act_bound.x < localx + this->collisionBoundXY.x) {
		if (act_pos.y + act_bound.y > localy - this->collisionBoundXY.y &&
			act_pos.y - act_bound.y < localy + this->collisionBoundXY.y) {
			onSide(a);

			if (this->m_Zlevel + collisionBoundZ.x > act_z - a->collisionBoundXY.x
				&& this->m_Zlevel - collisionBoundZ.y < act_z + a->collisionBoundZ.y) {

				if (m_Zlevel > act_z) {
					a->m_Zlevel = act_z - 1;
					a->vel.z = 0;
					onBottom(a);
				}
				//x 10 y -30 for Tweaking reason.
				if (this->m_Zlevel + collisionBoundZ.x > act_z - a->collisionBoundXY.x
					&& this->m_Zlevel - collisionBoundZ.y < act_z + a->collisionBoundZ.y) {
					auto vec = (act_pos - localPos());

					if (vec.length() > 0)vec /= vec.length();


					float aBoundx = a->collisionBoundXY.x + collisionBoundXY.x;
					float aBoundy = a->collisionBoundXY.y + collisionBoundXY.y;
					if (abs(vec.y) < abs(vec.x)) {
						if (act_pos.x > localx)act_pos.x = localx + aBoundx;
						if (act_pos.x < localx)act_pos.x = localx - aBoundx;
					}
					else {
						if (act_pos.y > localy)act_pos.y = localy + aBoundy;
						if (act_pos.y < localy)act_pos.y = localy - aBoundy;
					}

					a->setlocalPos(act_pos.x, act_pos.y);
					vec *= .05f;
					
					a->localVel(vec.x, vec.y);
					localVel(-vec.x, -vec.y);
					return true;
				}
				return true;
			}
		}
	}



	return false;



}
actor::m_direction actor::getDirection() {

	return m_direction::WEST;
}

float actor::drawShadow(actor* a) {
	auto cqq = a->DistanceFrom(this);
	lastDistance = cqq;
	alpha = 1 - cqq * 0.01f;

	return cqq;
}
 
void actor::Draw(SpriteBatch & renderer, bool selected) {
	if (!&m_chipset || !renderMe)return;
	glm::vec3 c = this->color  +this->fxColors;
	glm::vec2 p = this->pos;
	glm::vec2 s = this->size;
	auto uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	p.y -= (m_Zlevel / (55 / 33));

	p.y -= (m_chipset.Height);
	p.x -= 2;

	glm::vec2 spos = pos;

	spos.y -= platZ;
	//p.y -= zDepthOffset;
	float dyMiz = 1 + (platZ - m_Zlevel) * .001f;
	if (dyMiz > 1.2f)dyMiz = 1.2f;
	auto s2 = glm::vec2(100, 50);
	 if (FlipX)s2.x *= -1;

	//renderer.DrawSprite(shadow, spos + glm::vec2(0 - 2, 0), s2 * dyMiz, 0, glm::vec4(0, 0, 0, dyMiz));
	renderer.draw( glm::vec4(spos.x - 2 , spos.y +2,
		s2.x * dyMiz, s2.y * dyMiz),
		uvRect,
		m_chipshadow.ID, pos.y + zDepthOffset + platZ-10, glm::vec4(c, dyMiz));
	if (FlipX) {
		uvRect.x += 1.0f ; // this will add one tile over
		uvRect.z *= -1;
	}


	
	//	if (GHOSTLY)c*= .3f;
	//if (selected) p.y += 10;
	 if (FlipX) s.x *= -1;
	//	renderer.DrawSprite(this->img, p, s, this->GlobalRotation, c);
	 if (selected) {


		 renderer.draw(glm::vec4(p.x, p.y,
			 s.x, s.y),
			 glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
			 m_chipset.ID,999999, glm::vec4(0,0,0, .3));
		 return;
	 }
	renderer.draw(glm::vec4(p.x  , p.y  ,
		s.x  , s.y  ),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		m_chipset.ID, pos.y + zDepthOffset + m_Zlevel, glm::vec4(c * alpha, 1.5) );

	if (!&m_chipshadow)return;

}

bool actor::CollisionWithMe(glm::vec2 v) {
	if (!collideWithMe)return false;
	float x = this->localPos().x - .1f;
	float y = this->localPos().y - .1f;
	if (v.x > x - .5f && v.x < x + .5f)
		if (v.y > y - .5f && v.y < y + .5f)
			return true;

	return false;
}

void actor::update(float dt) {
 
	 
	 

	if (!physicsMe)return;
	this->pos.x += vel.x;
	this->pos.y += vel.y;
	// localMove( vel.y * dt, -vel.x * dt);
	this->m_Zlevel += vel.z;


	if (vel.x > 100)vel.x = 100;	if (vel.x < -100)vel.x = -100;
	if (vel.y > 100)vel.y = 100;	if (vel.y < -100)vel.y = -100;
	if (vel.z > 100)vel.z = 100;	if (vel.z < -100)vel.z = -100;
	if (!isOnGround && m_Zlevel > 0) vel.z -= 1.1f;
	if (abs(vel.length()) > 0) {
		vel.y *= .87f;
		vel.x *= .87f;
		if (vel.z > 0)
			vel.z *= .96f;
		else 	vel.z *= .95f;
	}

	if (m_Zlevel <= platZ && isOnGround) {
		m_Zlevel = platZ;
		if (vel.z < 0)vel.z = 0;
	}

}

void actor::update(Grid* g, float dt)
{

	update(dt);
}
