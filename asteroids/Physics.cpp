#include "Physics.h"
#include "PhysicsManager.h"

bool ComputeCollisionCircles(HandleBody first, HandleBody second, ArrayCollisions& collisions)
{
	Vec2 repiter = second->GetPosition() - first->GetPosition();
	Vec2 normal = Normalize(repiter);
	float depth = Length(repiter) - first->circleCollider->Radius - second->circleCollider->Radius;
	Vec2 position = first->GetPosition() + first->circleCollider->Radius * normal;

	if (depth < 0.0f)
	{
		HandleCollision collision(new Collision(position, normal, depth, first, second));
		collisions.push_back(collision);
	}

	return depth < 0.0f;
}

bool CheckCollision(HandleBody body1, HandleBody body2, float& overlap, Vec2& direct, Projection& pr1, Projection& pr2)
{
	HandleShellCollider first = body1->polygonCollider;
	HandleShellCollider second = body2->polygonCollider;
		
	for (size_t i = 0; i < second->normals.size(); i++)
	{
		Vec2& normal = second->normals[i];
		Projection p1 = first->ComputeProjection(normal);
		Projection p2 = second->ComputeProjection(normal);
		if (!p1.Overlap(p2) && !p2.Overlap(p1))
		{
			second->Swap(i, 0);
			return false;
		}
		else
		{
			float o = ComputeOverlap(p1, p2);
			//check contains
			if (ContainProjection(p1, p2))
			{
				float mins = fabs(p1.min - p2.min);
				float maxs = fabs(p1.max - p2.max);
				o += Min(mins, maxs);
			}

			if (o < overlap && p1 != p2)
			{
				overlap = o;
				direct = normal;

				pr1 = p1;
				pr2 = p2;
			}
		}
	}

	return true;
}

bool ComputeCollisionPolygons(HandleBody first, HandleBody second, ArrayCollisions& collisions)
{
	// обновить точные коллайдеры
	first->UpdateAccurateCollider();
	second->UpdateAccurateCollider();
	
	float overlap = std::numeric_limits<float>::max();
	Vec2 normal;
	Projection pr1;
	Projection pr2;

	//проверяем столкновение вершин с нормалями граней второго тела
	if (!CheckCollision(first, second, overlap, normal, pr1, pr2))
	{
		return false;
	}
	else
	{
		//затем проверяем столкновение вершин с нормалями граней первого тела
		if (!CheckCollision(second, first, overlap, normal, pr2, pr1))
		{
			return false;
		}
	}
	
	if (overlap == std::numeric_limits<float>::max())
		return false;

	//создаем столькновения
	CreateCollision(pr1, pr2, normal, first, second, collisions);	
	
	return collisions.size() > 0;
}

static Vec2 Middle(const Vec2& point1, const Vec2& point2)
{
	Vec2 point = Vec2((point1.x + point2.x) / 2, (point1.y + point2.y) / 2);
	return point;
}

static Vec2 Middle(Vec2 points[2], int pointsSize)
{
	Vec2 point;
	for (int i = 0; i < pointsSize; i++)
	{
		point += points[i];
	}
	point /= float(pointsSize);
	return point;
}

static int CalcContactPatch(Vec2 points1[2],
							int pointsSize1,
							Vec2 points2[2],
							int pointsSize2,
							Vec2& normal,
							std::vector<Vec2>& positions)
{
	if (pointsSize1 == 1 && pointsSize2 == 2)
	{	
		positions.push_back(points1[0]);		
		return 0;
	}
	else
	{
		if (pointsSize2 == 1 && pointsSize1 == 2)
		{				
			positions.push_back(points2[0]);
			
			return 1;
		}
		else
		{
			if (pointsSize2 == 1 && pointsSize1 == 1)
			{		
				positions.push_back(Middle(points1[0], points2[0]));
				return 2;
			}
		}
	}

	Vec2 dir = LeftNormal(1.0, normal);
	//пятно контакта
	float pt10 = Min(Dot(points1[0], dir), Dot(points1[1], dir));
	float pt11 = Max(Dot(points1[0], dir), Dot(points1[1], dir));

	float pt20 = Min(Dot(points2[0], dir), Dot(points2[1], dir));
	float pt21 = Max(Dot(points2[0], dir), Dot(points2[1], dir));

	if (pt10 > pt20 && pt10 < pt21)
	{
		positions.push_back(points1[0]);
		if (pt11 > pt21)
		{
			positions.push_back(points2[1]);
		}
		else
		{
			positions.push_back(points1[1]);
		}
	}
	else
	{
		if (pt11 > pt20 && pt11 < pt21)
		{
			positions.push_back(points1[1]);
			if (pt10 < pt20)
			{
				positions.push_back(points2[0]);
			}
			else
			{
				positions.push_back(points1[0]);
			}
		}
	}

	return 3;
}

static void CreateCollision(Projection& pr1, Projection& pr2, Vec2 normal, HandleBody b1, HandleBody b2, ArrayCollisions& collisions)
{
	std::vector<Vec2> positions;
	float overlap = 0.0f;
	if (pr2.max > pr1.min && pr2.min < pr1.min)
	{
		overlap = Min(pr2.max - pr1.min, pr1.min - pr2.min);
		if (overlap > 0.1f)
			overlap = overlap;
		if (pr2.max - pr1.min < pr1.min - pr2.min)
		{
			CalcContactPatch(pr1.minPoints, pr1.sizeMin, pr2.maxPoints, pr2.sizeMax, normal, positions);
			normal = -normal;
		}
		else
		{			
			CalcContactPatch(pr2.minPoints, pr2.sizeMin, pr1.minPoints, pr1.sizeMin, normal, positions);	
		}
	}
	else
	{
		if (pr2.max > pr1.max && pr2.min < pr1.max)
		{
			if (overlap > 0.1f)
				overlap = overlap;

			overlap = Min(pr2.max - pr1.max, pr1.max - pr2.min);
			if (pr2.max - pr1.max < pr1.max - pr2.min)
			{
				CalcContactPatch(pr1.maxPoints, pr1.sizeMax, pr2.maxPoints, pr2.sizeMax, normal, positions);				
			}
			else
			{
				CalcContactPatch(pr2.minPoints, pr2.sizeMin, pr1.maxPoints, pr1.sizeMax, normal, positions);	
				
			}
		}
		else
		{
			CreateCollision(pr2, pr1, normal, b2, b1, collisions);
		}
	}
	

	for (Vec2 position : positions)
	{
		HandleCollision collision;
		collision = std::shared_ptr<Collision>(new Collision(position, normal, overlap, b1, b2));
		collisions.push_back(collision);
	}
}

static float ComputeOverlap(Projection& pr1, Projection& pr2)
{
	float overlap = 0.0f;
	if (pr2.max > pr1.min && pr2.min < pr1.min)
	{
		overlap = Min(pr2.max - pr1.min, pr1.min - pr2.min);
	}
	else
	{
		if (pr2.max > pr1.max && pr2.min < pr1.max)
		{
			overlap = Min(pr2.max - pr1.max, pr1.max - pr2.min);
		}
	}

	return overlap;
}

static bool ContainProjection(Projection& pr1, Projection& pr2)
{
	return (pr1.min - PhysicsManager::Accuracy <= pr2.min && pr1.max + PhysicsManager::Accuracy >= pr2.max) || 
		   (pr2.min - PhysicsManager::Accuracy <= pr1.min && pr2.max + PhysicsManager::Accuracy >= pr1.max);
}