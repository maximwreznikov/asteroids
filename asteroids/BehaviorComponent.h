#ifndef BehaviorComponent_h
#define BehaviorComponent_h

#include <functional>

#include "Entity.h"
#include "EntityComponent.h"
#include "PhysicComponent.h"

class BehaviorComponent;
typedef std::shared_ptr<BehaviorComponent> HandleBehavior;
typedef std::function<void(HandleBody, HandleBody)> CollideEvent;

/**
@brief BehaviorComponent - компонент отвечающий за поведения объекта
@detailed Регистрируется в менеджере поведения(BehaviorManager), при возникновении соответствующего 
события BehaviorManager вызывает обработчик этого события из этого компонента
*/
class BehaviorComponent : public EntityComponent, public std::enable_shared_from_this<BehaviorComponent>
{
private:
	CollideEvent	_onCollide;								/**< коллбэк на столкновение с чем либо */
public:
	BehaviorComponent(const CollideEvent& onCollide);
	virtual ~BehaviorComponent();

	virtual void onAdd(){};
	virtual void onRemove(){};

	virtual void RegisterComponent(Owner entity) final;
	virtual void UnregisterComponent() final;

	void DispatchCollide(HandleBody ownBody, HandleBody otherbody);
};

#endif
