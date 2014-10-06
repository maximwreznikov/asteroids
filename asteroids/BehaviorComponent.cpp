#include "BehaviorComponent.h"

#include "Engine.h"
#include "EventManager.h"


BehaviorComponent::BehaviorComponent(const CollideEvent& onCollide)
{
	_onCollide = onCollide;
}


BehaviorComponent::~BehaviorComponent()
{
}

void BehaviorComponent::DispatchCollide(HandleBody ownBody, HandleBody otherbody)
{
	_onCollide(ownBody, otherbody);
}

void BehaviorComponent::UnregisterComponent()
{
	EntityComponent::UnregisterComponent();
	Engine::Instance()->GetEvents()->DetachComponent(GetOwner().lock(), shared_from_this());
}

void BehaviorComponent::RegisterComponent(Owner entity)
{
	EntityComponent::RegisterComponent(entity);
	Engine::Instance()->GetEvents()->AttachComponent(entity.lock(), shared_from_this());
}
