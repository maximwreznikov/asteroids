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
@brief ���� ���
*/
struct BodyPair
{
	HandleBody body1;
	HandleBody body2;

	float friction;								/**< ����� ������ */

	BodyPair(HandleBody b1, HandleBody b2);
	/**
	@brief ��������� ������������ �� ��������������� ����������
	*/
	bool CheckApproxCollide();
	/**
	@brief ������ �������
	@return true, ���� ���� ���� ���� �������
	*/
	bool SolveCollisions(float dt);
};


#endif