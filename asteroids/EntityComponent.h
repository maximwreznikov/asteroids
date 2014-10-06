#ifndef EntityComponent_h
#define EntityComponent_h

#include <memory>
#include <string>

class Entity;
typedef std::weak_ptr<Entity> Owner;

/**
@brief Компонент сущности, обособленная часть сущности взаимодействующая со своей подсистемой движка
*/
class EntityComponent
{
private:
	Owner _owner;					/**< сущность которой принадлежит компонент */
public:
	EntityComponent();
	virtual ~EntityComponent();

	/**
	@brief Функция вызываемая при инициализации компонента в движок
	*/
	virtual void onAdd() = 0;
	/**
	@brief Функция вызываемая при удалении компонента из движка
	*/
	virtual void onRemove() = 0;

	/**
	@brief Регистрация кмпонента в нужной подсистеме движка
	@detailed Установка _owner, регистрация к нужной подсистеме движка
	(например RendererComponent регистрируется в RenderManager)
	*/
	virtual void RegisterComponent(Owner entity);

	/**
	@brief Отсоединение от всех подсистем в которых компонент был зарегестрирован
	*/
	virtual void UnregisterComponent();

	Owner GetOwner();
};

#endif
