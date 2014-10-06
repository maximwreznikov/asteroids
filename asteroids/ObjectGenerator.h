#ifndef ObjectGenerator_h
#define ObjectGenerator_h

#include <random>
#include <ctime>

#include "Math.h"
#include "Entity.h"
#include "PhysicComponent.h"
#include "BehaviorComponent.h"

/**
@brief Колл бэки для столкновений
*/
void RemoveBullet(HandleBody ownBody, HandleBody otherBody);
void RemoveFragment(HandleBody ownBody, HandleBody otherBody);
void CollideAsteroidCallback(HandleBody ownBody, HandleBody otherBody);

class RandomDistribution
{
private:
	float _startValue;
	float _endValue;
public:
	RandomDistribution(float startValue, float endValue)
	{
		_startValue = startValue;
		_endValue = endValue;
	}

	float operator () ()
	{
		float value = _endValue - _startValue;
		float r = float(rand()) / float(RAND_MAX);
		return _startValue + value * r;
	}
};

/**
@brief Генератор игровых объектов
*/
class ObjectGenerator
{
private:
	const float size = 0.3f;																			/**< размер астероидов по умолчанию */

	void generateQuad(std::vector<Vec2>& outForm, float mWidth = 0.3f, float mHeight = 0.3f);
	void generateShellQuad(std::vector<Vec2>& polygon, float mWidth = 0.3f, float mHeight = 0.3f);
	void generateAsteroid(float radius, int npoint,
						std::vector<Vec2>& gAsteroid,
						std::vector<Vec2>& fAsteroid);
	void generateRandomAsteroid(float radius, int npoint,
							std::vector<Vec2>& gAsteroid,
							std::vector<Vec2>& fAsteroid);
	void generateShip(std::vector<Vec2>& form);
	static void addFragment(std::vector<Vec2> polygons, Mat3& matrix, Vec2 position, Vec2 velocity, float angularVelocity, float mass);

public:
	const float ShipWidth = 0.35f;
	const float ShipHeight = 0.4f;

	HandleEntity AppendAsteroid(Vec2 pos = Vec2(), Vec2 velocity = Vec2(), float angularVelocity = 0.0f, float mass = 5.0f);
	HandleEntity AppendRandomAsteroid(Vec2 pos = Vec2(), Vec2 velocity = Vec2(), float angularVelocity = 0.0f, float mass = 5.0f);
	void AddBullet(Vec2 pos, Vec2 velocity = Vec2(0.0f, 0.4f));
	HandleEntity CreateShip(Vec2 pos, CollideEvent callback);
	static void AddFragments(Mat3 matrix, Vec2& pos, Vec2& velocity, float mass, float xsize, float ysize);
	
	void AppendWall();

};

#endif