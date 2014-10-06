#include "EventManager.h"


EventManager::EventManager()
{
}


EventManager::~EventManager()
{
}

void EventManager::AttachComponent(HandleEntity entity, HandleBehavior newBehavior)
{
	EngineManager<HandleBehavior>::AttachComponent(entity, newBehavior);
	_behaviors[entity] = newBehavior;
}

bool EventManager::DetachComponent(HandleEntity entity, HandleBehavior component)
{
	bool ok = EngineManager<HandleBehavior>::DetachComponent(entity, component);

	_behaviors.erase(entity);

	return ok;
}

void EventManager::CallCollide(HandleBody body1, HandleBody body2)
{
	HandleEntity entity1 = body1->GetOwner().lock();
	HandleEntity entity2 = body2->GetOwner().lock();
	HandleBehavior behavior1 = _behaviors[entity1];
	HandleBehavior behavior2 = _behaviors[entity2];
	
	if (behavior1 != nullptr) behavior1->DispatchCollide(body1, body2);
	if (behavior2 != nullptr) behavior2->DispatchCollide(body2, body1);
}
