#ifndef Physics_h
#define Physics_h

#include "Collision.h"
#include "PhysicComponent.h"

/**
@brief ���������� ������������ ���� �������� �� ������ ���������� �����������
@param first ������ ������
@param second ������ ������
@return collisions ��������� ������������
@return true, ���� ������������ �������
*/
bool ComputeCollisionCircles(HandleBody first, HandleBody second, ArrayCollisions& collisions);
bool ComputeCollisionPolygons(HandleBody first, HandleBody second, ArrayCollisions& collisions);

/**
@brief �������� �� ������������ ���� ��������
@param body1 ������ ������
@param body2 ������ ������
@param overlap ��������� ����������� ����������
@param direct ������ �� �������� ���������� ����������� ����������
@param pr1 ��������� ������������
@return true, ���� ������������ �������
*/
static bool CheckCollision(HandleBody body1, HandleBody body2, float& overlap, Vec2& direct, Projection& pr1, Projection& pr2);

/**
@brief �������� ���������� ��������
@param pr1 ������ ��������
@param pr2 ������ ��������
@return �������� ����������
*/
static float ComputeOverlap(Projection& pr1, Projection& pr2);

/**
@brief ������� ������������
@param pr1 �������� ������� ����
@param pr2 �������� ������� ����
@param normal ������� ����� ������� ���������� ������������
@param b1 ������ ����
@param b2 ������ ����
@return collisions �������������
*/
static void CreateCollision(Projection& pr1, Projection& pr2, Vec2 normal, HandleBody b1, HandleBody b2, ArrayCollisions& collisions);

/**
@brief ��������� �������� �� ���� �������� ������
@param pr1 ������ ��������
@param pr2 ������ ��������
@return true, ���� ��������
*/
static bool ContainProjection(Projection& pr1, Projection& pr2);

#endif