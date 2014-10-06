#ifndef Transformation_h
#define Transformation_h

#include "Math.h"

/**
@brief Class for set orientation & position of something
@detailed
*/
class Transformation
{
public: 
	static Mat4 GWorldMatrix;				// Multiplied view * projection matrix

private:	
	Mat3 _modelMatrix;
	Mat4 _modelInWorldMatrix;
public:

	Transformation();
	virtual ~Transformation();

	void SetMatrix(const Mat3& newModelMatrix);
	const Mat4& GetMatrix();
	const Mat3& GetOwnMatrix();

	virtual void Rotate(float angle);
	virtual void Translate(float x, float y);

	Vec2 GetPosition();
	void SetPosition(Vec2 newPos);

	float GetX();
	float GetY();
	void SetX(float);
	void SetY(float);
};



#endif

