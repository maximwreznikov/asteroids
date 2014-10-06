#ifndef EntityComponent_h
#define EntityComponent_h

#include <memory>
#include <string>

class Entity;
typedef std::weak_ptr<Entity> Owner;

/**
@brief ��������� ��������, ������������ ����� �������� ����������������� �� ����� ����������� ������
*/
class EntityComponent
{
private:
	Owner _owner;					/**< �������� ������� ����������� ��������� */
public:
	EntityComponent();
	virtual ~EntityComponent();

	/**
	@brief ������� ���������� ��� ������������� ���������� � ������
	*/
	virtual void onAdd() = 0;
	/**
	@brief ������� ���������� ��� �������� ���������� �� ������
	*/
	virtual void onRemove() = 0;

	/**
	@brief ����������� ��������� � ������ ���������� ������
	@detailed ��������� _owner, ����������� � ������ ���������� ������
	(�������� RendererComponent �������������� � RenderManager)
	*/
	virtual void RegisterComponent(Owner entity);

	/**
	@brief ������������ �� ���� ��������� � ������� ��������� ��� ���������������
	*/
	virtual void UnregisterComponent();

	Owner GetOwner();
};

#endif
