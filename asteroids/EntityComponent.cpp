#include "EntityComponent.h"
#include "Entity.h"


EntityComponent::EntityComponent()
{
}

EntityComponent::~EntityComponent()
{
}

void EntityComponent::RegisterComponent(Owner entity)
{
	_owner = entity;
}

void EntityComponent::UnregisterComponent()
{
	_owner.reset();
}

Owner EntityComponent::GetOwner()
{
	return _owner;
}
