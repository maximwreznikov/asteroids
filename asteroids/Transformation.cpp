#include "Transformation.h"

Mat4 Transformation::GWorldMatrix = Mat4();

Transformation::Transformation()
{
	SetMatrix(Mat3());
}


Transformation::~Transformation()
{
}

void Transformation::SetMatrix(const Mat3& newModelMatrix)
{
	_modelMatrix = newModelMatrix;
	_modelInWorldMatrix = GWorldMatrix * _modelMatrix;
}

const Mat3& Transformation::GetOwnMatrix()
{
	return _modelMatrix;
}

const Mat4& Transformation::GetMatrix()
{
	return _modelInWorldMatrix;
}

void Transformation::Rotate(float angle)
{
	_modelMatrix.Rotate(angle);
	SetMatrix(_modelMatrix);
}

void Transformation::Translate(float x, float y)
{
	_modelMatrix.Translate(Vec2(x, y));
	SetMatrix(_modelMatrix);
}

Vec2 Transformation::GetPosition()
{
	return Vec2(GetX(), GetY());
}

float Transformation::GetX()
{
	return _modelMatrix[2][0];
}

float Transformation::GetY()
{
	return _modelMatrix[2][1];
}

void Transformation::SetPosition(Vec2 newPos)
{
	_modelMatrix[2][0] = newPos.x;
	_modelMatrix[2][1] = newPos.y;
	SetMatrix(_modelMatrix);
}

void Transformation::SetX(float x)
{
	_modelMatrix[2][0] = x;
	SetMatrix(_modelMatrix);
}
void Transformation::SetY(float y)
{
	_modelMatrix[2][1] = y;
	SetMatrix(_modelMatrix);
}


