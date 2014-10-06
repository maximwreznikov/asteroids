#include "PhysicsManager.h"

#include <algorithm>

#include "Pairs.h"
#include "Engine.h"
#include "EventManager.h"

const float PhysicsManager::Accuracy = 0.01f;
const float PhysicsManager::kAllowedPenetration = 0.01f;
const float PhysicsManager::kBounceFactor = 0.2f;

PhysicsManager::PhysicsManager()
{
}


PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::AttachComponent(HandleEntity entity, HandleBody newBody)
{
	for (HandleBody body : _components)
	{
		std::shared_ptr<BodyPair> pair(new BodyPair(body, newBody));
		_pairs.push_back(pair);
	}

	EngineManager<HandleBody>::AttachComponent(entity, newBody);
}

bool PhysicsManager::DetachComponent(HandleEntity entity, HandleBody component)
{
	bool ok = EngineManager<HandleBody>::DetachComponent(entity, component);

	//удалить пару
	_pairs.erase(std::remove_if(_pairs.begin(), _pairs.end(),
	[=](std::shared_ptr<BodyPair> pair)->bool
	{
		if (pair->body1 == component || pair->body2 == component)
			return true;

		return false;
	}), _pairs.end());

	return ok;
}

void PhysicsManager::OnFrame(float dt)
{	
	//update all body position
	for (auto body : _components)
	{
		body->onFrame(dt);
	}
	
	std::vector<std::pair<HandleBody, HandleBody>> collides;
	collides.reserve(_pairs.size() * 2);
	for (size_t i = 0; i < _pairs.size(); i ++)
	{		
		std::shared_ptr<BodyPair>& pair = _pairs[i];
		if (pair->CheckApproxCollide())
		{
			if (pair->SolveCollisions(dt))
			{
				collides.push_back(std::pair<HandleBody, HandleBody>(pair->body1, pair->body2));
			}
		}		
	}

	//вызов callback`ов подвешенных на столкновение тел
	for (auto pair : collides)
	{
		Engine::Instance()->GetEvents()->CallCollide(pair.first, pair.second);
	}
	collides.clear();	
}

