#include "Entity.h"

#include <algorithm>

#include "Engine.h"
#include "EntityComponent.h"


Entity::Entity(EntityTypes type)
{
	_type = type;
}


Entity::~Entity()
{
	RemoveComponents();
}

void Entity::AddComponent(HandleComponent component)
{
	_components.push_back(component); 
}

bool Entity::RemoveComponent(HandleComponent component)
{
	auto posObjects = std::find(_components.begin(), _components.end(), component);
	bool found = posObjects != _components.end();

	if (found)
	{
		(*posObjects)->UnregisterComponent();
		_components.erase(posObjects);
	}

	return found;
}

void Entity::RemoveComponents()
{
	for (auto component : _components)	
		component->onRemove();
	
	_components.clear();
}

Transformation& Entity::Transformation()
{
	return _transformation;
}

const HandleComponents& Entity::GetComponents()
{
	return _components;
}

EntityTypes Entity::GetType()
{
	return _type;
}
