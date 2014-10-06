#include "Pairs.h"
#include "Physics.h"

BodyPair::BodyPair(HandleBody b1, HandleBody b2)
{
	body1 = b1;
	body2 = b2;

	friction = 0.5f;
}

bool BodyPair::CheckApproxCollide()
{
	float distance = Distance(body2->GetPosition(), body1->GetPosition());

	if (distance > body1->circleCollider->Radius + body2->circleCollider->Radius)
		return false;

	return true;
}


bool BodyPair::SolveCollisions(float dt)
{	
	ArrayCollisions collisions;
	ComputeCollisionPolygons(body1, body2, collisions);	

	for (auto c : collisions)
	{
		c->SolveCollision(c, dt, friction);
	}

	return collisions.size() > 0;
}