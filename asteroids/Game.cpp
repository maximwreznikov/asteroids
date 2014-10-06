#include "Game.h"

#include <algorithm>
#include <random>
#include <ctime>

#include "Engine.h"
#include "RenderManager.h"

Game::Game()
{
	srand(time(0));
}

Game::~Game()
{
}

/**
@brief Коллбэк на столкновение чего-либо с кораблём
@param ownBody корабль
@param body тело сталкивающееся с кораблем
*/
void Game::collideShipCallback(HandleBody ownBody, HandleBody body)
{
	HandleEntity owner = ownBody->GetOwner().lock();
	Engine::Instance()->LazyRemoveEntity(owner);
	_playing = false;
}

void Game::TestScene()
{
	_objectGenerator.AppendAsteroid(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f), 0.0f);

	_objectGenerator.AppendAsteroid(Vec2(-1.2f, 0.1f), Vec2(0.2f, 0.0f), 0.0f, 5.1f);
	//_objectGenerator.AppendAsteroid(Vec2(1.2f, 0.1f), Vec2(-0.2f, 0.0f), 0.0f, 5.1f);

	_objectGenerator.AppendAsteroid(Vec2(-0.31f, 1.2f), Vec2(0.0f, -0.2f), 0.0f);
	//_objectGenerator.AppendAsteroid(Vec2(0.31f, -1.2f), Vec2(0.0f, 0.25f), 0.0f, 5.1f);


	//_objectGenerator.AddBullet(Vec2(0.0f, -1.2f), Vec2(0.0f, 0.3f));	

	//auto callback = [=](HandleBody owner, HandleBody body){collideShipCallback(owner, body); };
	//_spaceShip = _objectGenerator.CreateShip(Vec2(0.0f, 0.0f), callback);
	//_playing = true;	
}

void Game::GameScene()
{
	Engine::Instance()->ClearAll();

	auto callback = [=](HandleBody owner, HandleBody body){collideShipCallback(owner, body); };
	_spaceShip = _objectGenerator.CreateShip(Vec2(0.0f, 0.0f), callback);
	

	_objectGenerator.AppendRandomAsteroid(Vec2(1.5f, 1.9f), Vec2(-0.03f, -0.15f), 0.15f);
	_objectGenerator.AppendRandomAsteroid(Vec2(-1.5f, 1.7f), Vec2(0.02f, -0.2f), 0.0f, 3.0f);

	_objectGenerator.AppendRandomAsteroid(Vec2(-0.5f, 2.0f), Vec2(0.03f, -0.15f), 0.0f, 3.6f);

	_playing = true;
}

bool Game::Update(float dt)
{
	current_time += dt;
	
	if (_playing && current_time > update_time)
	{
		cleanup();
		Engine::Instance()->Cleanup();
		GenerateNewAsteroid();
		current_time = 0.0f;
	}

	return _playing;
}

/**
@brief Удалить астероиды вышедшие из поля зрения
*/
void Game::cleanup()
{
	_asteroids.remove_if([=](HandleEntity entity)->bool
	{
		Vec2 position = entity->Transformation().GetPosition();
		if (fabs(position.x) > getViewWidth()  ||
			fabs(position.y) > getViewHeight() ||
			!entity->isActive)
		{
			Engine::Instance()->RemoveEntity(entity);
			return true;
		}

		return false;
	});
}

/**
@brief Выстрел из корабля
*/
void Game::Shot()
{
	if (_playing)
	{
		Vec2 pos = _spaceShip->Transformation().GetPosition();
		_objectGenerator.AddBullet(pos + Vec2(0.0f, _objectGenerator.ShipHeight + 0.01f), bullet_velocity);
	}
}

/**
@brief Передвижение корабля
@param dx, dy смещения корабля относительно старых координат
@param t время смещения
*/
void Game::Move(float dx, float dy, float dt)
{
	if (_playing)
	{
		Vec2 position = _spaceShip->Transformation().GetPosition();
		Vec2 velocity(dx / Engine::Instance()->GetRenderer()->ScaleX, dy / Engine::Instance()->GetRenderer()->ScaleY);
		velocity = ship_speed * Normalize(velocity);

		_spaceShip->Transformation().SetX(position.x + velocity.x * dt);
		_spaceShip->Transformation().SetY(position.y + velocity.y * dt);
	}
}

/**
@brief Сгенерировать новый случайный астероид
*/
void Game::GenerateNewAsteroid()
{
	if (_asteroids.size() >= max_asteroids)
		return;

	RandomDistribution xrandom(-getViewWidth(), getViewWidth());
	RandomDistribution yrandom(getViewHeight(), getViewHeight());
	RandomDistribution speedremdom(asteroid_min_speed, asteroid_max_speed);

	Vec2 position(xrandom(), yrandom());
	Vec2 velocity = speedremdom() * Normalize(Vec2(xrandom(), 0.0f) - position);
	_asteroids.push_back(_objectGenerator.AppendRandomAsteroid(position, velocity));
}

float Game::getViewWidth()
{
	return Engine::Instance()->GetRenderer()->GetViewWidth() + Engine::Instance()->MaxObjectSize;
}

float Game::getViewHeight()
{
	return Engine::Instance()->GetRenderer()->GetViewHeight() + Engine::Instance()->MaxObjectSize;
}
