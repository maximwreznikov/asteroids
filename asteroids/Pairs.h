#ifndef BodyPair_h
#define BodyPair_h

#include <vector>

#include "PhysicComponent.h"
#include "Colliders.h"
#include "Collision.h"

struct BodyPairKey;
struct BodyPair;

typedef std::pair<BodyPairKey, BodyPair> BPairKey;

/**
@brief ѕара тел
*/
struct BodyPair
{
	HandleBody body1;
	HandleBody body2;

	float friction;								/**< общее трение */

	BodyPair(HandleBody b1, HandleBody b2);
	/**
	@brief ѕроверить сталкиваютс€ ли приблизительные коллайдеры
	*/
	bool CheckApproxCollide();
	/**
	@brief –ешить контакт
	@return true, если есть хоть один контакт
	*/
	bool SolveCollisions(float dt);
};


#endif