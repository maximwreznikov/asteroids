#ifndef Game_h
#define Game_h

#include <list>

#include "ObjectGenerator.h"

class Game
{
private:
	const size_t 				max_asteroids = 8;
	const float					update_time = 7.0f;
	const float					ship_speed = 0.8f;
	const float					asteroid_max_speed = 0.5f;
	const float					asteroid_min_speed = 0.1f;
	const Vec2					bullet_velocity = Vec2(0.0f, 0.81f);
	float						current_time = 0.0f;

	HandleEntity				_spaceShip;								/**< наш корабль */
	ObjectGenerator				_objectGenerator;						/**< генератор объектов */
	std::list<HandleEntity>		_asteroids;								/**< астероиды */

	bool						_playing;								/**< флаг окончания игры */

	float getViewWidth();
	float getViewHeight();

	void cleanup();
	void collideShipCallback(HandleBody owner, HandleBody body);
public:
	Game();
	~Game();

	bool Update(float dt);

	void Shot();
	void Move(float x, float y, float dt);
	void GenerateNewAsteroid();

	void GameScene();
	void TestScene();
};

#endif

