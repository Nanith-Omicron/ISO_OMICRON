#pragma once
#include "tile.h"

//Pre Collision 
void tile::preCollision(actor* a) {


	float tempDist = a->DistanceFrom(this);
	float b = m_Zlevel + H;
	if (a->m_Zlevel + 20 >= b)a->platZ = b;

	if (tempDist > cullingUpdate * cullingUpdate)return;
	if (tempDist > collisionBoundXY.x + .15f)return;


	CollisionWithMe(a);
}


//Set the Color Saturation based on distance
float tile::tileShadow(actor * a) {

	float dist = a->DistanceFrom(this);
	alpha = 1.125 - ((45 + dist) * 0.016);//0.014
	return dist;
}

//Collision routine AABB +CC
bool tile::CollisionWithMe(actor * a) {

	float localx = this->localPos().x;
	float localy = this->localPos().y;
	
	glm::vec2 act_pos = a->localPos();
	
	float act_z = a->m_Zlevel;
	glm::vec2 act_bound = a->collisionBoundXY;
	bool grd = false;
	//To fired off events. We do not take the Actual size in count. 
	if (act_pos.x > localx - 1 && act_pos.x < localx + 1)
		if (act_pos.y > localy - 1 && act_pos.y < localy + 1)
			//40
			if (this->m_Zlevel + 25 > act_z && this->m_Zlevel < act_z + 30) {
				onTop(a);
				if (this->m_Zlevel > act_z && this->m_Zlevel < act_z + 1)
					if (a->vel.z < 0 || (a->m_Zlevel + a->vel.z) < m_Zlevel)a->vel.z = 0;

				if ((act_z + a->vel.z) < m_Zlevel)act_z = 0;

				grd = true;
				a->m_Zlevel = m_Zlevel + 2;
				//if(!a->isOnGround && a->vel.z < 1)a->vel.z = 15;




			}

	//Collision Side
	if (act_pos.x + act_bound.x > localx - this->collisionBoundXY.x &&
		act_pos.x - act_bound.x < localx + this->collisionBoundXY.x) {
		if (act_pos.y + act_bound.y > localy - this->collisionBoundXY.y &&
			act_pos.y - act_bound.y < localy + this->collisionBoundXY.y) {

			if (this->m_Zlevel + collisionBoundZ.x > act_z - a->collisionBoundXY.x
				&& this->m_Zlevel - collisionBoundZ.y < act_z + a->collisionBoundZ.y) {

				if (m_Zlevel > act_z) {
					a->m_Zlevel = act_z - 1;
					a->vel.z = 0;
					onBottom(a);
				}
				//x 10 y -30 for Tweaking reason.
				if (this->m_Zlevel + collisionBoundZ.x > act_z - a->collisionBoundXY.x + 10
					&& this->m_Zlevel - collisionBoundZ.y < act_z + a->collisionBoundZ.y - 30) {
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
					vec *= .04f;
					onSide(a);
					a->localVel(vec.x, vec.y);
					return true;
				}
				return true;
			}
		}
	}



	return false;
}


//Fired up on collision when an Actor is on top
void tile::onTop(actor * a) {
	Tile_Displace_Effect = 12.0f;
	a->isOnGround = true;
}

//Fired up on collision when an actor is on it sides
void tile::onSide(actor * a) {

}

//Tick off each update
void tile::update(float td) {

	//Set the offset to it Z value + 50
	zDepthOffset = m_Zlevel + 50;
	//Ease into initiale position

	// Displacing Effects on tile
	if (Tile_Displace_Effect > 0) {

		Tile_Displace_Effect -= td * 900;
	}
	else {
		Tile_Displace_Effect = 0;
	}

}

//Fast Collision method
bool tile::CollisionWithMe(glm::vec2 v) {

	float x = this->localPos().x - .1f;
	float y = this->localPos().y - .1f;
	if (v.x > x - collisionBoundXY.x && v.x < x + collisionBoundXY.x)
		if (v.y > y - collisionBoundXY.y && v.y < y + collisionBoundXY.y)
			return true;

	return false;
}

void tile::update(Grid * g, float dt)
{


}

float tile::drawShadow(actor * a)
{
	return  actor::drawShadow(a);
}

// Common DRAW routine
void  tile::Draw(SpriteBatch & renderer, bool selected) {
	
	if (!&m_chipset)return; 

	glm::vec3 c = this->color;	
	glm::vec2 p = this->pos;
	float Visibility = 1;
	p.y -= (m_Zlevel - Tile_Displace_Effect);

	if (layer==m_layer::GHOSTLY)c * .3f;
	if (invisibleByProximity && alpha != 0 && !alwaysProximityVisible)Visibility = 3.7f - 4 * alpha;
	if (Visibility < .4) Visibility = 0;

	if (selected || this->selected) { c *= 0.3f; }
	if (justInvisible)Visibility = 0;

	renderer.draw(
		glm::vec4(p.x, p.y,
			size.x, size.y),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		m_chipset.ID, pos.y + zDepthOffset + m_Zlevel,
		glm::vec4(c * alpha, Visibility));
}