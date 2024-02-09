#pragma once
#include "actor.h"


class item :public actor{


public:

	virtual void update(float dt);
	virtual void onSide(actor * a);
	virtual void use(actor* a);
	virtual void onGet(actor* a);
 
	virtual void onDrop(actor* a);
	virtual bool CollisionWithMe(actor* a);
	virtual void Draw(SpriteBatch& renderer, bool selected = false);
	
	bool hasOwner() {
		return owner != nullptr;
	}
	actor* owner;
	glm::vec2 collisionBoundXY = glm::vec2(.1f), collisionBoundZ =glm::vec2(7.5f, 32.5f);
	Texture2D UI_img;
	double value = 100;
	int amount = 1;
	bool autoPickup = true;
	double pickupRange = .8;
	int item_ID;
	double _internTimer = 0;
	
};