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
@brief BehaviorComponent - ��������� ���������� �� ��������� �������
@detailed �������������� � ��������� ���������(BehaviorManager), ��� ������������� ���������������� 
������� BehaviorManager �������� ���������� ����� ������� �� ����� ����������
*/
class BehaviorComponent : public EntityComponent, public std::enable_shared_from_this<BehaviorComponent>
{
private:
	CollideEvent	_onCollide;								/**< ������� �� ������������ � ��� ���� */
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
