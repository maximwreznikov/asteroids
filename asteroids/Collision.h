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
@brief Проекция тела на ось
*/
struct Projection
{
	float	min;													/**< минимум */
	float	max;													/**< максимум */

	Vec2	minPoints[2];											/**< точки дающие минимальную проекцию */
	Vec2	maxPoints[2];											/**< точки дающие максимальную проекцию */
	int		sizeMin;												/**< количество точек дающих минимальную проекцию */
	int		sizeMax;												/**< количество точек дающих максимальную проекцию */

	Projection();
	Projection(float max_, float min_, const Edge& point);
	void ProjectEdge(float value1, const Edge& edge);
	bool Overlap(const Projection& pr);
	bool Contain(const Projection& pr);
	bool operator ==(const Projection& pr);
	bool operator !=(const Projection& pr);
};

/**
@brief Данные о столкновении
@detailed Данные для обработки столкновения
*/
struct Collision
{
	Collision(Vec2 pos, Vec2 n, float d, HandleBody b1, HandleBody b2);

	/**
	@brief Решить контакт
	@param с контакт
	@param dt время контакта
	@param friction трение между объектами
	*/
	void SolveCollision(HandleCollision c, float dt, float friction);

	Vec2 position;														/**< точка контакта */
	Vec2 normal;														/**< нормаль по которой происходит контакт */
	Vec2 r1, r2;														/**< радиус-векторы до центров масс тел участвующих в столкновении */
	float depth;														/**< глубина взаимопроникновения тел при контакте */
	float massNormal, massTangent;										/**< тангенциальная и нормальная масса */
	float bounce;														/**< параметр для выталкивания тел из друг друга */

	HandleBody body1;													/**< первое тело участвующее в контакте */
	HandleBody body2;													/**< второе тело участвующее в контакте */
};


#endif