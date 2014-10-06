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
@brief Все типы сущностей 
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
@brief Entity - сущность, объект в игровом движке 
@detailed Содержит в себе компоненты, отвечающие за поведение сущности
(отрисовку, физическое взаимодействие и т.п.) и общие для компонентов свойства,
Слабая ссылка на сущность пробрасывается в каждый компонент при добавлении
сущности в движок - функция Engine::AppendEntity, удаляется при удалении - 
функцией Engine::RemoveEntity
*/
class Entity
{
private:
	Transformation		_transformation;				/**< матрица трансформации */
	HandleComponents	_components;					/**< компоненты сущности */
	EntityTypes			_type;							/**< тип сщности */
	
public:
	bool				isActive;						/**< активна ли сущность */

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

