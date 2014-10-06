#ifndef Collision_h
#define Collision_h

#include <vector>
#include <memory>

#include "Math.h"
#include "PhysicComponent.h"

struct Collision;
struct Projection;

typedef std::shared_ptr<Collision> HandleCollision;
typedef std::vector<std::shared_ptr<Collision>> ArrayCollisions;

/**
@brief �������� ���� �� ���
*/
struct Projection
{
	float	min;													/**< ������� */
	float	max;													/**< �������� */

	Vec2	minPoints[2];											/**< ����� ������ ����������� �������� */
	Vec2	maxPoints[2];											/**< ����� ������ ������������ �������� */
	int		sizeMin;												/**< ���������� ����� ������ ����������� �������� */
	int		sizeMax;												/**< ���������� ����� ������ ������������ �������� */

	Projection();
	Projection(float max_, float min_, const Edge& point);
	void ProjectEdge(float value1, const Edge& edge);
	bool Overlap(const Projection& pr);
	bool Contain(const Projection& pr);
	bool operator ==(const Projection& pr);
	bool operator !=(const Projection& pr);
};

/**
@brief ������ � ������������
@detailed ������ ��� ��������� ������������
*/
struct Collision
{
	Collision(Vec2 pos, Vec2 n, float d, HandleBody b1, HandleBody b2);

	/**
	@brief ������ �������
	@param � �������
	@param dt ����� ��������
	@param friction ������ ����� ���������
	*/
	void SolveCollision(HandleCollision c, float dt, float friction);

	Vec2 position;														/**< ����� �������� */
	Vec2 normal;														/**< ������� �� ������� ���������� ������� */
	Vec2 r1, r2;														/**< ������-������� �� ������� ���� ��� ����������� � ������������ */
	float depth;														/**< ������� ������������������� ��� ��� �������� */
	float massNormal, massTangent;										/**< �������������� � ���������� ����� */
	float bounce;														/**< �������� ��� ������������ ��� �� ���� ����� */

	HandleBody body1;													/**< ������ ���� ����������� � �������� */
	HandleBody body2;													/**< ������ ���� ����������� � �������� */
};


#endif