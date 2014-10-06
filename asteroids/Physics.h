#ifndef Physics_h
#define Physics_h

#include "Collision.h"
#include "PhysicComponent.h"

/**
@brief Рассчитать столкновение двух объектов на основе упрощенных коллайдеров
@param first первый объект
@param second второй объект
@return collisions найденные столкновения
@return true, если столкновения найдены
*/
bool ComputeCollisionCircles(HandleBody first, HandleBody second, ArrayCollisions& collisions);
bool ComputeCollisionPolygons(HandleBody first, HandleBody second, ArrayCollisions& collisions);

/**
@brief Проверка на столкновение двух объектов
@param body1 первый объект
@param body2 второй объект
@param overlap найденное минимальное перекрытие
@param direct вектор по которому происходит минимальное перекрытие
@param pr1 найденные столкновения
@return true, если столкновения найдены
*/
static bool CheckCollision(HandleBody body1, HandleBody body2, float& overlap, Vec2& direct, Projection& pr1, Projection& pr2);

/**
@brief Рачитать перекрытие проекций
@param pr1 первая проекция
@param pr2 вторая проекция
@return значение перекратия
*/
static float ComputeOverlap(Projection& pr1, Projection& pr2);

/**
@brief Создать столкновение
@param pr1 проекция первого тела
@param pr2 проекция второго тела
@param normal нормаль вдоль которой происходит столкновение
@param b1 первое тело
@param b2 второе тело
@return collisions столконовения
*/
static void CreateCollision(Projection& pr1, Projection& pr2, Vec2 normal, HandleBody b1, HandleBody b2, ArrayCollisions& collisions);

/**
@brief Проверить содержит ли одна проекция другую
@param pr1 первая проекция
@param pr2 вторая проекция
@return true, если содержит
*/
static bool ContainProjection(Projection& pr1, Projection& pr2);

#endif