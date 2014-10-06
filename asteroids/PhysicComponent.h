#ifndef PhysicComponent_h
#define PhysicComponent_h

#include <vector>

#include "Math.h"
#include "EntityComponent.h"
#include "Colliders.h"

class PhysicComponent;
typedef std::shared_ptr<PhysicComponent> HandleBody;

/**
@brief Компонент отвечает за физические свойства сущности
@detailed Хранит все основные физические свойства и набор коллайдеров для физического движка 
*/
class PhysicComponent : public EntityComponent, public std::enable_shared_from_this<PhysicComponent>
{
private:
	std::vector<Vec2>			_vertices;			/**< набор вершин для расчета столкновений */
	bool						_outdated;			/**< нужно ли обновить коллайдер */
	Mat3						_updatedMatrix;		/**< матрица трансформации для последнего обновления коллайдера*/

	float calcMomentum();

public:
	Vec2						velocity;			/**< угловое ускорение */
	float						angularVelocity;	/**< угловая сокрость */

	float						mass;				/**< масса */
	float						inverseMass;		/**< обратная масса */
	float						momentum;			/**< момент инерции */
	float						inverseMomentum;	/**< обратный момент инерции */

	float						friction;			/**< трение */

	HandleCircleCollider		circleCollider;		/**< простой коллайдер для приблизительной оценки столкновения */
	HandleShellCollider			polygonCollider;	/**< коллайдер для точной оценки столконовения */


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

