#include "Engine.h"

#include <memory> 
#include <iostream>
#include <algorithm>

#include "Entity.h"
#include "RenderManager.h"
#include "PhysicsManager.h"
#include "EventManager.h"

Engine::Engine()
{
	// ������������� ������, �������� ���� ��������
	_renderer = std::shared_ptr<RenderManager>(new RenderManager());
	_physics = std::shared_ptr<PhysicsManager>(new PhysicsManager());
	_events = std::shared_ptr<EventManager>(new EventManager());
}

Engine::~Engine()
{
}

Engine* Engine::Instance()
{
	static Engine instance;
	return &instance;
}

/**
@brief ������������� ����������� ����������
*/
void Engine::SetupGraphics(int w, int h)
{
	_renderer->InitView(w, h);
}

/**
@brief �������� �������� � ������
@param entity ����� ��������
*/
void Engine::AppendEntity(HandleEntity entity)
{
	entity->isActive = true;
	_entities.push_back(entity);
	for (auto component : entity->GetComponents())
	{
		component->RegisterComponent(entity);
		component->onAdd();
	}
}

/**
@brief ������� ����������� ��� �������� �������
*/
void Engine::_removeEntity(HandleEntity entity)
{
	// ������� ��� ���������� �������� �� ������
	for (auto component : entity->GetComponents())
	{
		component->onRemove();
		component->UnregisterComponent();
	}
}

/**
@brief ���������� ������� �������� �� ������
@param entity �������� ��������
*/
bool Engine::RemoveEntity(HandleEntity entity)
{
	entity->isActive = false;
	// ������� �������� �� ������
	auto posObjects = std::find(_entities.begin(), _entities.end(), entity);
	bool found = posObjects != _entities.end();

	if (found)
	{
		_removeEntity(entity);
		_entities.erase(posObjects);
	}

	return found;
}

/**
@brief ��������� ������� �������� �� ������
@param entity �������� ��������
*/
void Engine::LazyRemoveEntity(HandleEntity entity)
{
	entity->isActive = false;
	_toremove.push_back(entity);
}

/**
@brief ��������� ���������
@param dt ����� ��������� � �������� ���������
*/

void Engine::OnFrame(float dt)
{	
	_renderer->Render();	
	_physics->OnFrame(dt);	

	//do lazy remove entities	
	for (int i = 0; i < _toremove.size(); i++)
	{
		RemoveEntity(_toremove[i]);
	}
	_toremove.clear();
}

/**
@brief ������� ������ ������
@detailed ������� ������� ������� ��������� �� ������
*/
void Engine::Cleanup()
{
	auto toremove = std::remove_if(_entities.begin(), _entities.end(), [=](HandleEntity entity)->bool
	{
		Vec2 position = entity->Transformation().GetPosition();
		if (fabs(position.x) > (_renderer->GetViewWidth() + MaxObjectSize) ||
			fabs(position.y) > (_renderer->GetViewHeight() + MaxObjectSize))
		{
			_removeEntity(entity);
			return true;
		}

		return false;
	});

	if (toremove != _entities.end())
		_entities.erase(toremove, _entities.end());
}

/**
@brief ������� ��� �������
*/
void Engine::ClearAll()
{
	//do lazy remove entities	
	for (int i = 0; i < _entities.size(); i++)
	{
		_removeEntity(_entities[i]);
	}
	_entities.clear();
}

std::shared_ptr<RenderManager> Engine::GetRenderer()
{
	return _renderer;
}

std::shared_ptr<PhysicsManager> Engine::GetPhysics()
{
	return _physics;
}

std::shared_ptr<EventManager> Engine::GetEvents()
{
	return _events;
}


