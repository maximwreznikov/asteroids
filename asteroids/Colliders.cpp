#include "Colliders.h"

#include "Math.h"
#include "Collision.h"

CircleCollider::CircleCollider(const std::vector<Vec2>& vertices)
{
	Radius = 0;
	for (Vec2 vertex : vertices)
	{
		if (Radius < Length(vertex))
		{
			Radius = Length(vertex);
		}
	}

	if (Radius == 0) Radius = 0.01f;
}

ShellCollider::ShellCollider(const std::vector<Vec2>& vertices)
{
	for (size_t i = 0; i < vertices.size(); i++)
	{
		Vec2 vertex1 = vertices[i];
		Vec2 vertex2 = vertices[i + 1 == vertices.size() ? 0 : i + 1];
		Vec2 edge = vertex2 - vertex1;
		Vec2 normal = Normalize(LeftNormal(1.0f, edge));
		float length = Distance(vertex1, vertex2);
		edges.push_back(Edge(vertex1, vertex2, length));
		transformedEdges.push_back(Edge(vertex1, vertex2, length));
		normals.push_back(normal);
	}
}

void ShellCollider::Update(Mat3 transform)
{
	transformedEdges.clear();
	normals.clear();
	if (edges.size() == 1)
	{
		Vec2 vertex1 = transform * edges[0].vertex1;
		Vec2 vertex2 = transform * edges[0].vertex2;		
		transformedEdges.push_back(Edge(vertex1, vertex2, edges[0].length));
	}
	else
	{
		for (Edge face : edges)
		{
			Vec2 vertex1 = transform * face.vertex1;
			Vec2 vertex2 = transform * face.vertex2;
			Vec2 edge = vertex2 - vertex1;
			Vec2 normal = Normalize(LeftNormal(1.0f, edge));
			transformedEdges.push_back(Edge(vertex1, vertex2, face.length));
			normals.push_back(normal);
		}
	}
}

Projection ShellCollider::ComputeProjection(Vec2 axis)
{
	float min = Dot(transformedEdges[0].vertex1, axis);
	float max = min;
	Projection projection(max, min, transformedEdges[0]);
	for (int i = 1; i < transformedEdges.size(); i++)
	{
		Edge& edge = transformedEdges[i];
		float pr1 = Dot(edge.vertex1, axis);
		projection.ProjectEdge(pr1, edge);
	}
	
	return projection;
}

void ShellCollider::Swap(int f, int s)
{
	Edge tmp = edges[f];
	edges[f] = edges[s];
	edges[s] = tmp;

	tmp = transformedEdges[f];
	transformedEdges[f] = transformedEdges[s];
	transformedEdges[s] = tmp;

	Vec2 tmpv = normals[f];
	normals[f] = normals[s];
	normals[s] = tmpv;
}