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
	// Инициализация движка, создание всех посистем
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
@brief Инициализация графической подсистемы
*/
void Engine::SetupGraphics(int w, int h)
{
	_renderer->InitView(w, h);
}

/**
@brief Добавить сущность в движок
@param entity новая сущность
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
@brief Функция выполняемая при удалении объекта
*/
void Engine::_removeEntity(HandleEntity entity)
{
	// удалить все компоненты сущности из движка
	for (auto component : entity->GetComponents())
	{
		component->onRemove();
		component->UnregisterComponent();
	}
}

/**
@brief Немедленно удалить сущность из движка
@param entity удалемая сущность
*/
bool Engine::RemoveEntity(HandleEntity entity)
{
	entity->isActive = false;
	// удалить сущность из движка
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
@brief Отложенно удалить сущность из движка
@param entity удалемая сущность
*/
void Engine::LazyRemoveEntity(HandleEntity entity)
{
	entity->isActive = false;
	_toremove.push_back(entity);
}

/**
@brief Обработка изменений
@param dt время прошедшее с последне обработки
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
@brief Удалить лишние обекты
@detailed Функция удаляет объекты невидимые на экране
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
@brief Удалить все объекты
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


