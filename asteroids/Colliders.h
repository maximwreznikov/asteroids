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
@brief �������� ��������� ��� �������
*/
struct CircleCollider
{
	float Radius;								/**< ������ ���������� */

	CircleCollider(const std::vector<Vec2>&);
};

/**
@brief ����� ��������
*/
struct Edge
{
	Vec2 vertex1;								/**< ������ ���������� ����� */
	Vec2 vertex2;								/**< ������ ���������� ����� */
	float length;								/**< ����� ����� */

	Edge(Vec2 v1, Vec2 v2, float len) :vertex1(v1), vertex2(v2), length(len){}
};


/**
@brief ������������� ��������� ��� �������
*/
struct ShellCollider
{
	std::vector<Edge> edges;					/**< ����� ���� */
	std::vector<Edge> transformedEdges;			/**< ������������������ ����� ���� */
	std::vector<Vec2> normals;			/**< ������������������ ����� ���� */

	ShellCollider(const std::vector<Vec2>&);
	/**
	@brief �������� ������ � ����������� � �������� ����������
	@param transform ������� ������������� ����
	*/
	void Update(Mat3 transform);
	/**
	@brief ��������� �������� ���� �� ���
	*/
	Projection ComputeProjection(Vec2 axis);

	/**
	@brief �������� ����� �������
	*/
	void Swap(int first, int second);
};

#endif