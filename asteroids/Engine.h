#ifndef Engine_h
#define Engine_h

#include <memory>
#include <vector>
#include <map>
#include <functional>

#include "Entity.h"
#include "EntityComponent.h"
#include "RendererComponent.h"

class RenderManager;
class PhysicsManager;
class EventManager;

/**
@brief Engine - игровой движок нашей игры
@detailed Игровой движок сделан на распространенном принципе построения движков Entity-Component,
используемом например в Unity3d
*/
class Engine
{
private:
	Engine();
	~Engine();
	Engine(const Engine&);
	Engine& operator=(const Engine&);

	std::vector<HandleEntity>				_entities;			/**< сущности обрабатываемые движком */

	std::shared_ptr<RenderManager>			_renderer;			/**< подсистема графики */
	std::shared_ptr<PhysicsManager>			_physics;			/**< подситема физики */
	std::shared_ptr<EventManager>			_events;			/**< подсистема событий */

	std::vector<HandleEntity>				_toremove;			/**< сущности для удаление в конце такта */

	void _removeEntity(HandleEntity entity);
public:	
	const float								MinObjectSize = 0.15f;		/**< Минимальный размер объектов */
	const float								MaxObjectSize = 0.7f;		/**< Максимальный размер объектов */

	static Engine* Instance();

	void SetupGraphics(int w, int h);
	void OnFrame(float dt);
	void Cleanup();
	void ClearAll();

	void AppendEntity(HandleEntity entity);
	bool RemoveEntity(HandleEntity entity);
	void LazyRemoveEntity(HandleEntity entity);

	std::shared_ptr<RenderManager> GetRenderer();
	std::shared_ptr<PhysicsManager> GetPhysics();
	std::shared_ptr<EventManager> GetEvents();
};
#endif

