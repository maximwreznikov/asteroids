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
@brief Engine - ������� ������ ����� ����
@detailed ������� ������ ������ �� ���������������� �������� ���������� ������� Entity-Component,
������������ �������� � Unity3d
*/
class Engine
{
private:
	Engine();
	~Engine();
	Engine(const Engine&);
	Engine& operator=(const Engine&);

	std::vector<HandleEntity>				_entities;			/**< �������� �������������� ������� */

	std::shared_ptr<RenderManager>			_renderer;			/**< ���������� ������� */
	std::shared_ptr<PhysicsManager>			_physics;			/**< ��������� ������ */
	std::shared_ptr<EventManager>			_events;			/**< ���������� ������� */

	std::vector<HandleEntity>				_toremove;			/**< �������� ��� �������� � ����� ����� */

	void _removeEntity(HandleEntity entity);
public:	
	const float								MinObjectSize = 0.15f;		/**< ����������� ������ �������� */
	const float								MaxObjectSize = 0.7f;		/**< ������������ ������ �������� */

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

