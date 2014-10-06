#ifndef Entity_h
#define Entity_h

#include <memory>
#include <vector>

#include "Transformation.h"

class Entity;
class EntityComponent;
enum class EntityTypes;

typedef std::vector<std::shared_ptr<EntityComponent>> HandleComponents;
typedef std::shared_ptr<EntityComponent> HandleComponent;
typedef std::shared_ptr<Entity> HandleEntity;

/**
@brief ��� ���� ��������� 
*/
enum class EntityTypes
{
	DEFAULT,
	ASTEROID,
	FRAGMENT,
	SHIP,
	BULLET
};

/**
@brief Entity - ��������, ������ � ������� ������ 
@detailed �������� � ���� ����������, ���������� �� ��������� ��������
(���������, ���������� �������������� � �.�.) � ����� ��� ����������� ��������,
������ ������ �� �������� �������������� � ������ ��������� ��� ����������
�������� � ������ - ������� Engine::AppendEntity, ��������� ��� �������� - 
�������� Engine::RemoveEntity
*/
class Entity
{
private:
	Transformation		_transformation;				/**< ������� ������������� */
	HandleComponents	_components;					/**< ���������� �������� */
	EntityTypes			_type;							/**< ��� ������� */
	
public:
	bool				isActive;						/**< ������� �� �������� */

	Entity(EntityTypes type = EntityTypes::DEFAULT);
	~Entity();

	void AddComponent(HandleComponent component);
	bool RemoveComponent(HandleComponent component);
	void RemoveComponents();

	Transformation& Transformation();
	const HandleComponents& GetComponents();

	EntityTypes GetType();	
};



#endif

