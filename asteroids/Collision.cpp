#include "Collision.h"
#include "PhysicsManager.h"

Projection::Projection()
{
	max = std::numeric_limits<float>::min();
	min = std::numeric_limits<float>::max();
	sizeMin = 0;
	sizeMax = 0;
}

Projection::Projection(float max_, float min_, const Edge& edge) : max(max_), min(min_)
{
	maxPoints[0] = edge.vertex1;
	minPoints[0] = edge.vertex1;
	sizeMin = 1;
	sizeMax = 1;
}

void Projection::ProjectEdge(float value, const Edge& edge)
{
	bool added = false;
	if (fabs(value - min) < edge.length / 10.0f)
	{
		if (sizeMin > 1)
			sizeMin = 1;
		minPoints[sizeMin] = edge.vertex1;
		sizeMin++;
		added = true;
	}

	if (fabs(value - max) < edge.length / 10.0f)
	{
		if (sizeMax > 1)
			sizeMax = 1;
		maxPoints[sizeMax] = edge.vertex1;
		sizeMax++;
		added = true;
	}

	if (!added)
	{

		if (value < min)
		{
			min = value;
			sizeMin = 1;
			minPoints[0] = edge.vertex1;
		}
		//else
		//{
		if (value > max)
		{
			max = value;
			sizeMax = 1;
			maxPoints[0] = edge.vertex1;
		}
		//}
	}
}

bool Projection::Overlap(const Projection& pr)
{
	return (pr.max > min && pr.min < min) || 
		   (pr.max > max && pr.min < max);
}

bool Projection::Contain(const Projection& pr)
{
	return min <= pr.min + 0.1 && max + 0.1 >= pr.max;
}

bool Projection::operator ==(const Projection& pr)
{
	return (fabs(min - pr.min) < PhysicsManager::Accuracy) && (fabs(max - pr.max) < PhysicsManager::Accuracy);
}

bool Projection::operator !=(const Projection& pr)
{
	return !operator ==(pr);
}

Vec2 Middle(const std::vector<Vec2>& points)
{
	Vec2 point;
	for (Vec2 pnt : points)
	{
		point += pnt;
	}
	point /= points.size();
	return point;
}

void Collision::SolveCollision(HandleCollision c, float dt, float friction)
{
	HandleBody b1 = c->body1;
	HandleBody b2 = c->body2;

	// –ассчитать нормальный импульс
	// –асчет относительной скорости при контакте
	Vec2 dv = b2->velocity + LeftNormal(b2->angularVelocity, c->r2)
			- b1->velocity - LeftNormal(b1->angularVelocity, c->r1);

	float vn = Dot(dv, c->normal);

	float dPn = c->massNormal * (-vn + c->bounce / dt);

	dPn = Max(dPn, 0.0f);

	// ѕридать телу рассчитанный нормальный импульс
	Vec2 Pn = dPn * c->normal;
	b1->AddImpulse(-Pn, c->r1);
	b2->AddImpulse(Pn, c->r2);

	// обновить скорость с точке контакта дл€ расчета тангенциального импульса
	dv = b2->velocity + LeftNormal(b2->angularVelocity, c->r2)
	   - b1->velocity - LeftNormal(b1->angularVelocity, c->r1);

	Vec2 tangent = RightNormal(c->normal, 1.0f);
	float vt = Dot(dv, tangent);
	float dPt = c->massTangent * (-vt);

	float maxPt = friction * dPn;
	dPt = Middle(dPt, -maxPt, maxPt);

	// ѕридать телу рассчитанный тангенциальный импульс
	Vec2 Pt = dPt * tangent;
	b1->AddImpulse(-Pt, c->r1);
	b2->AddImpulse(Pt, c->r2);
}

Collision::Collision(Vec2 pos, Vec2 n, float d, HandleBody b1, HandleBody b2)
{
	position = pos;
	normal = n;
	depth = d;
	body1 = b1;
	body2 = b2;

	r1 = position - b1->GetPosition();
	r2 = position - b2->GetPosition();

	// –ассчитать нормальную массу, тангенциальную массу и отскок
	float rn1 = Dot(r1, normal);
	float rn2 = Dot(r2, normal);
	float kNormal = b1->inverseMass + b2->inverseMass;
	kNormal += b1->inverseMomentum * (Dot(r1, r1) - rn1 * rn1) + b2->inverseMomentum * (Dot(r2, r2) - rn2 * rn2);
	massNormal = 1.0f / kNormal;

	Vec2 tangent = RightNormal(normal, 1.0f);
	float rt1 = Dot(r1, tangent);
	float rt2 = Dot(r2, tangent);
	float kTangent = b1->inverseMass + b2->inverseMass;
	kTangent += b1->inverseMomentum * (Dot(r1, r1) - rt1 * rt1) + b2->inverseMomentum * (Dot(r2, r2) - rt2 * rt2);
	massTangent = 1.0f / kTangent;

	bounce = -PhysicsManager::kBounceFactor * Min(0.0f, depth + PhysicsManager::kAllowedPenetration);
}