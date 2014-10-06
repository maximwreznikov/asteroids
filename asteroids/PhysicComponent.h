#ifndef PhysicComponent_h
#define PhysicComponent_h

#include <vector>

#include "Math.h"
#include "EntityComponent.h"
#include "Colliders.h"

class PhysicComponent;
typedef std::shared_ptr<PhysicComponent> HandleBody;

/**
@brief ��������� �������� �� ���������� �������� ��������
@detailed ������ ��� �������� ���������� �������� � ����� ����������� ��� ����������� ������ 
*/
class PhysicComponent : public EntityComponent, public std::enable_shared_from_this<PhysicComponent>
{
private:
	std::vector<Vec2>			_vertices;			/**< ����� ������ ��� ������� ������������ */
	bool						_outdated;			/**< ����� �� �������� ��������� */
	Mat3						_updatedMatrix;		/**< ������� ������������� ��� ���������� ���������� ����������*/

	float calcMomentum();

public:
	Vec2						velocity;			/**< ������� ��������� */
	float						angularVelocity;	/**< ������� �������� */

	float						mass;				/**< ����� */
	float						inverseMass;		/**< �������� ����� */
	float						momentum;			/**< ������ ������� */
	float						inverseMomentum;	/**< �������� ������ ������� */

	float						friction;			/**< ������ */

	HandleCircleCollider		circleCollider;		/**< ������� ��������� ��� ��������������� ������ ������������ */
	HandleShellCollider			polygonCollider;	/**< ��������� ��� ������ ������ ������������� */


	PhysicComponent(const std::vector<Vec2>& vertices,
					float mass = 0.0f,
					Vec2 velocity = Vec2(),
					float angularVelocity = 0.0f);

	virtual ~PhysicComponent();

	virtual void onAdd();
	virtual void onRemove();
	virtual void onFrame(float dt);

	virtual void RegisterComponent(Owner entity) final;
	virtual void UnregisterComponent() final;

	Vec2 GetPosition();
	Mat3 GetMatrix();

	void AddImpulse(Vec2 impulse, Vec2 localPoint);
	void UpdateAccurateCollider();
};

#endif

