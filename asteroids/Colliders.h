#ifndef Colliders_h
#define Colliders_h

#include <vector>
#include <memory>
#include "Math.h"

struct Projection;
struct CircleCollider;
struct ShellCollider;

typedef std::shared_ptr<CircleCollider> HandleCircleCollider;
typedef std::shared_ptr<ShellCollider> HandleShellCollider;

/**
@brief Круговой коллайдер для объекта
*/
struct CircleCollider
{
	float Radius;								/**< радиус коллайдера */

	CircleCollider(const std::vector<Vec2>&);
};

/**
@brief Грань полигона
*/
struct Edge
{
	Vec2 vertex1;								/**< первая координата грани */
	Vec2 vertex2;								/**< вторая координата грани */
	float length;								/**< длина грани */

	Edge(Vec2 v1, Vec2 v2, float len) :vertex1(v1), vertex2(v2), length(len){}
};


/**
@brief Полигональный коллайдер для объекта
*/
struct ShellCollider
{
	std::vector<Edge> edges;					/**< грани тела */
	std::vector<Edge> transformedEdges;			/**< трансформированные грани тела */
	std::vector<Vec2> normals;			/**< трансформированные грани тела */

	ShellCollider(const std::vector<Vec2>&);
	/**
	@brief Обновить данные о координатах и нормалях коллайдера
	@param transform матрица трансформации тела
	*/
	void Update(Mat3 transform);
	/**
	@brief Расчитать проекцию тела на ось
	*/
	Projection ComputeProjection(Vec2 axis);

	/**
	@brief Поменять грани местами
	*/
	void Swap(int first, int second);
};

#endif