#include "ObjectGenerator.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "Engine.h"
#include "PolygonRenderer.h"
#include "ShellRenderer.h"
#include "BulletRenderer.h"
#include "BehaviorComponent.h"
#include "shaders.h"

/**
@brief Коллбэк на столкновение чего-либо с пулей
@param owner пуля
@param body тело сталкивающееся с пулей
*/
void RemoveBullet(HandleBody ownbody, HandleBody body)
{
	HandleEntity owner = ownbody->GetOwner().lock();
	Engine::Instance()->LazyRemoveEntity(owner);
}

/**
@brief Коллбэк на столкновение чего-либо с фрагментом
@param ownbody фрагмент
@param body тело сталкивающееся с фрагментом
*/
void RemoveFragment(HandleBody ownbody, HandleBody body)
{
	HandleEntity enemy = body->GetOwner().lock();
	if (enemy->GetType() == EntityTypes::BULLET)
	{
		HandleEntity owner = ownbody->GetOwner().lock();
		Engine::Instance()->LazyRemoveEntity(owner);
	}
}

void CollideAsteroidCallback(HandleBody ownbody, HandleBody body)
{
	HandleEntity owner = ownbody->GetOwner().lock();
	HandleEntity enemy = body->GetOwner().lock();

	if (enemy->GetType() == EntityTypes::BULLET)
	{
		Mat3 matrix = owner->Transformation().GetOwnMatrix();
		Vec2 pos = owner->Transformation().GetPosition();
		Vec2 velocity = ownbody->velocity;
		float mass = ownbody->mass / 3.0f;
		float size = ownbody->circleCollider->Radius / 2.5f;

		Engine::Instance()->LazyRemoveEntity(owner);
		//generate fragment
		ObjectGenerator::AddFragments(matrix, pos, velocity, mass, size, size);
	}
}

HandleEntity ObjectGenerator::AppendAsteroid(Vec2 pos, Vec2 velocity, float angularVelocity, float mass)
{
	std::shared_ptr<Entity> entity(new Entity(EntityTypes::ASTEROID));
	entity->Transformation().SetPosition(pos);

	std::vector<Vec2> graphic;
	std::vector<Vec2> form;
	generateAsteroid(size, 5, graphic, form);

	std::shared_ptr<PolygonRenderer> polygon(new PolygonRenderer(graphic, glPositionColor_vert, glPositionColor_frag));
	entity->AddComponent(polygon);
	std::shared_ptr<ShellRenderer> shell(new ShellRenderer(form, glShellVertex, glBlueFragment));
	entity->AddComponent(shell);

	std::shared_ptr<PhysicComponent> body(new PhysicComponent(form, mass, velocity, angularVelocity));
	entity->AddComponent(body);

	HandleBehavior behavior(new BehaviorComponent(CollideAsteroidCallback));
	entity->AddComponent(behavior);

	Engine::Instance()->AppendEntity(entity);

	return entity;
}

HandleEntity ObjectGenerator::AppendRandomAsteroid(Vec2 pos, Vec2 velocity, float angularVelocity, float mass)
{
	std::shared_ptr<Entity> entity(new Entity(EntityTypes::ASTEROID));
	entity->Transformation().SetPosition(pos);
	RandomDistribution angle(0.0f, 90.0f);
	entity->Transformation().Rotate(angle());

	RandomDistribution size(Engine::Instance()->MinObjectSize, Engine::Instance()->MaxObjectSize);

	std::vector<Vec2> graphic;
	std::vector<Vec2> form;
	generateRandomAsteroid(size(), 4 + rand() % 4, graphic, form);

	std::shared_ptr<PolygonRenderer> polygon(new PolygonRenderer(graphic, glPositionColor_vert, glPositionColor_frag));
	entity->AddComponent(polygon);
	
	std::shared_ptr<PhysicComponent> body(new PhysicComponent(form, mass, velocity, angularVelocity));
	entity->AddComponent(body);

	HandleBehavior behavior(new BehaviorComponent(CollideAsteroidCallback));
	entity->AddComponent(behavior);

	Engine::Instance()->AppendEntity(entity);

	return entity;
}

void ObjectGenerator::AddFragments(Mat3 matrix, Vec2& pos, Vec2& velocity, float mass, float xsize, float ysize)
{
	matrix[2][0] = 0.0f;
	matrix[2][1] = 0.0f;
	Vec2 dypos(0.0f, ysize);
	Vec2 dyvelocity(0.0f, 0.005f + velocity.y / 5);
	std::vector<Vec2> upFragment;
	upFragment.push_back(Vec2(0.0f, -ysize));
	upFragment.push_back(Vec2(xsize, ysize));
	upFragment.push_back(Vec2(-xsize, ysize));
	addFragment(upFragment, matrix, pos + (matrix * dypos), velocity - (matrix * dyvelocity), 0.0f, mass);

	Vec2 dxpos(xsize, 0.0f);
	Vec2 dxvelocity(0.005f + velocity.x / 5, 0.0f);
	std::vector<Vec2> leftFragment;
	leftFragment.push_back(Vec2(xsize, 0.0f));
	leftFragment.push_back(Vec2(-xsize, ysize));
	leftFragment.push_back(Vec2(-xsize, -ysize));
	addFragment(leftFragment, matrix, pos - (matrix * dxpos), velocity - (matrix * dxvelocity), 0.0f, mass);

	std::vector<Vec2> rightFragment;
	rightFragment.push_back(Vec2(-xsize, 0.0f));
	rightFragment.push_back(Vec2(xsize, ysize));
	rightFragment.push_back(Vec2(xsize, -ysize));
	addFragment(rightFragment, matrix, pos + (matrix * dxpos), velocity + (matrix * dxvelocity), 0.0f, mass);
}

void ObjectGenerator::addFragment(std::vector<Vec2> polygons, Mat3& matrix, Vec2 position, Vec2 velocity, float angularVelocity, float mass)
{
	std::shared_ptr<Entity> entity(new Entity(EntityTypes::FRAGMENT));
	entity->Transformation().SetMatrix(matrix);
	entity->Transformation().SetPosition(position);

	std::shared_ptr<PolygonRenderer> shell(new PolygonRenderer(polygons, glPositionColor_vert, glPositionColor_frag));
	entity->AddComponent(shell);

	std::shared_ptr<PhysicComponent> body(new PhysicComponent(polygons, mass, velocity, angularVelocity));
	entity->AddComponent(body);

	HandleBehavior behavior(new BehaviorComponent(RemoveFragment));
	entity->AddComponent(behavior);

	Engine::Instance()->AppendEntity(entity);
}

void ObjectGenerator::AppendWall()
{
	std::shared_ptr<Entity> wall(new Entity());

	wall->Transformation().SetX(0.0f);
	wall->Transformation().SetY(-1.2f);

	std::vector<Vec2> form;
	generateQuad(form, 2.5f, 0.3f);
	std::shared_ptr<PolygonRenderer> polygon(new PolygonRenderer(form, glPositionColor_vert, glPositionColor_frag));
	wall->AddComponent(polygon);

	std::shared_ptr<PhysicComponent> body(new PhysicComponent(form, 100));
	wall->AddComponent(body);

	Engine::Instance()->AppendEntity(wall);
}

void ObjectGenerator::generateQuad(std::vector<Vec2>& outForm, float mWidth, float mHeight)
{
	outForm.push_back(Vec2(-mWidth / 2, -mHeight / 2));
	outForm.push_back(Vec2(mWidth / 2, -mHeight / 2));
	outForm.push_back(Vec2(-mWidth / 2, mHeight / 2));
	outForm.push_back(Vec2(mWidth / 2, mHeight / 2));
}

void ObjectGenerator::generateShellQuad(std::vector<Vec2>& polygon, float mWidth, float mHeight)
{
	float hwidth, hheight;
	hwidth = mWidth / 2;
	hheight = mHeight / 2;

	polygon.push_back(Vec2(-hwidth, hheight));
	polygon.push_back(Vec2(-hwidth, -hheight));
	polygon.push_back(Vec2(hwidth, -hheight));
	polygon.push_back(Vec2(hwidth, hheight));
}

void ObjectGenerator::generateAsteroid(float radius,
	int npoint,
	std::vector<Vec2>& gAsteroid,
	std::vector<Vec2>& fAsteroid)
{
	float step = float(2 * M_PI) / npoint;
	float currentAngle = 0;

	for (int i = 0; i < npoint; i++)
	{
		gAsteroid.push_back(Vec2(0.0f, 0.0f));
		gAsteroid.push_back(Vec2(radius * sin(currentAngle), radius * cos(currentAngle)));
		gAsteroid.push_back(Vec2(radius * sin(currentAngle + step), radius * cos(currentAngle + step)));

		fAsteroid.push_back(Vec2(radius * sin(currentAngle + step), radius * cos(currentAngle + step)));

		currentAngle += step;
	}
}

void ObjectGenerator::generateRandomAsteroid(float radius,
											int npoint,
											std::vector<Vec2>& gAsteroid,
											std::vector<Vec2>& fAsteroid)
{
	float halfstep = (float(2 * M_PI) / npoint) / 2.0f;
	RandomDistribution rangle(halfstep / 1.5f, halfstep);
	float currentAngle = 0;

	for (int i = 0; i < npoint; i++)
	{
		float step = i == npoint - 1 ? float(2 * M_PI) - currentAngle : halfstep + rangle();

		gAsteroid.push_back(Vec2(0.0f, 0.0f));
		gAsteroid.push_back(Vec2(radius * sin(currentAngle), radius * cos(currentAngle)));
		gAsteroid.push_back(Vec2(radius * sin(currentAngle + step), radius * cos(currentAngle + step)));

		fAsteroid.push_back(Vec2(radius * sin(currentAngle + step), radius * cos(currentAngle + step)));

		currentAngle += step;
	}
}

void ObjectGenerator::generateShip(std::vector<Vec2>& form)
{
	form.push_back(Vec2(0.0f, ShipHeight));
	form.push_back(Vec2(ShipWidth / 2, 0.0));
	form.push_back(Vec2(-ShipWidth / 2, 0.0));
}

void ObjectGenerator::AddBullet(Vec2 position, Vec2 velocity)
{
	std::shared_ptr<Entity> entity(new Entity(EntityTypes::BULLET));
	entity->Transformation().SetPosition(position);

	std::shared_ptr<BulletRenderer> bullet(new BulletRenderer());
	entity->AddComponent(bullet);

	HandleBehavior eventHandler(new BehaviorComponent(RemoveBullet));
	entity->AddComponent(eventHandler);

	std::vector<Vec2> vertices;
	vertices.push_back(Vec2(0.0f, 0.0f));
	HandleBody body(new PhysicComponent(vertices, 0.1f, velocity));
	entity->AddComponent(body);

	Engine::Instance()->AppendEntity(entity);
}

HandleEntity ObjectGenerator::CreateShip(Vec2 position, CollideEvent callback)
{
	std::shared_ptr<Entity> entity(new Entity(EntityTypes::SHIP));
	entity->Transformation().SetPosition(position);

	std::vector<Vec2> form;
	generateShip(form);

	std::shared_ptr<ShellRenderer> hull(new ShellRenderer(form, glShellVertex, glRedFragment));
	entity->AddComponent(hull);

	std::shared_ptr<PhysicComponent> body(new PhysicComponent(form, 7.0f));
	entity->AddComponent(body);

	HandleBehavior behavior(new BehaviorComponent(callback));
	entity->AddComponent(behavior);

	Engine::Instance()->AppendEntity(entity);

	return entity;
}
