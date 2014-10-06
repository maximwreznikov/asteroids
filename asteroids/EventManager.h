#ifndef BehaviorManager_h
#define BehaviorManager_h

#include <map>

#include "EngineManager.h"
#include "BehaviorComponent.h"
#include "PhysicComponent.h"
#include "Entity.h"


/**
@brief Менеджер событий
*/
class EventManager : public EngineManager<HandleBehavior>
{
private:
	std::map<HandleEntity, HandleBehavior> _behaviors;
public:
	EventManager();
	virtual ~EventManager();

	virtual void AttachComponent(HandleEntity entity, HandleBehavior component) override;
	virtual bool DetachComponent(HandleEntity entity, HandleBehavior component) override;

	void CallCollide(HandleBody body1, HandleBody body2);
};

#endif

