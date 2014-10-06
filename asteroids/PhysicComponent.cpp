#include "PhysicComponent.h"

#include "Engine.h"
#include "PhysicsManager.h"
#include "Pairs.h"
#include "Collision.h"
#include "Math.h"


PhysicComponent::PhysicComponent(const std::vector<Vec2>& vs,
								 float m, 
								 Vec2 v,
								 float av)
{
	_vertices = vs;

	mass = m;

	velocity = v;
	angularVelocity = av;

	momentum = 0.0f;
	friction = 0.05f;

	_outdated = true;
}

PhysicComponent::~PhysicComponent()
{
}

void PhysicComponent::onAdd()
{
	momentum = calcMomentum();
	inverseMass = 1.0f / mass;
	inverseMomentum = 1.0f / momentum;

	circleCollider = std::shared_ptr<CircleCollider>(new CircleCollider(_vertices));
	polygonCollider = std::shared_ptr<ShellCollider>(new ShellCollider(_vertices));

	_updatedMatrix = GetMatrix();
}

void PhysicComponent::onRemove()
{}

void PhysicComponent::onFrame(float dt)
{	
	std::shared_ptr<Entity> entity = GetOwner().lock();

	//calc position
	Vec2 oldPosition = GetPosition();
	Vec2 newPositon = oldPosition + velocity * dt;
	entity->Transformation().SetPosition(newPositon);

	//calc rotation
	float _angle = angularVelocity * dt;
	entity->Transformation().Rotate(_angle);
		
	if (angularVelocity != 0.0f || velocity.x != 0.0f || velocity.y != 0.0f) _outdated = true;
}

void PhysicComponent::UnregisterComponent()
{
	EntityComponent::UnregisterComponent();
	Engine::Instance()->GetPhysics()->DetachComponent(GetOwner().lock(), shared_from_this());
}

void PhysicComponent::RegisterComponent(Owner entity)
{
	EntityComponent::RegisterComponent(entity);
	Engine::Instance()->GetPhysics()->AttachComponent(entity.lock(), shared_from_this());
}

void PhysicComponent::UpdateAccurateCollider()
{
	Mat3 newMatrix = GetMatrix();
	if (_outdated || _updatedMatrix != newMatrix)
	{
		_updatedMatrix = newMatrix;
		polygonCollider->Update(_updatedMatrix);
		_outdated = false;
	}
}

Vec2 PhysicComponent::GetPosition()
{
	return GetOwner().lock()->Transformation().GetPosition();
}

Mat3 PhysicComponent::GetMatrix()
{
	return GetOwner().lock()->Transformation().GetOwnMatrix();
}

void PhysicComponent::AddImpulse(Vec2 impulse, Vec2 localPoint)
{
	//recompute body velocity & angularVelocity
	velocity += impulse / mass;
	angularVelocity += Cross(localPoint, impulse) / momentum;
	_outdated = true;
}

float PhysicComponent::calcMomentum()
{
	float topPart = 0;
	float bottomPart = 0;

	if (_vertices.size() <= 1)
		return mass * 0.01f * 0.01f / 2.0f;
	

	for (size_t i = 0; i < _vertices.size() - 1; i++)
	{
		Vec2 a = _vertices[i];
		Vec2 b = _vertices[i + 1];

		float mulVector = Cross(a, b);
		float sqrVectors = Dot(a, a) + Dot(a, b) + Dot(b, b);

		topPart += mulVector * sqrVectors;
		bottomPart += mulVector;
	}

	return (topPart / bottomPart) *  mass / 6;
}

