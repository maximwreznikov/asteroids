#include "Math.h"

float& Vec2::operator[](size_t i)
{
	assert(i < size());
	return (&x)[i];
}

Mat3::Mat3()
{
	for (size_t i = 0; i < size(); i++)
	{
		for (size_t j = 0; j < size(); j++)
		{
			_column[i][j] = i == j ? 1.0f : 0.0f;
		}
	}
}

Mat3::Mat3(float angle, Vec2 translate_) :Mat3()
{
	float c = cosf(angle), s = sinf(angle);
	_column[0][0] = c; _column[1][0] = -s;
	_column[0][1] = s; _column[1][1] = c;
	_column[2] = translate_;
}

Mat3::Mat3(float a, float b, float c, float d, float tx, float ty, float w) :Mat3()
{
	_column[0][0] = a; _column[1][0] = b;
	_column[0][1] = c; _column[1][1] = d;
	_column[2][0] = tx;
	_column[2][1] = ty;
	_column[2][2] = w;
}

Vec2& Mat3::operator[](size_t i)
{
	assert(i < size());
	return _column[i];
}

void Mat3::operator *= (Mat3 m)
{
	Mat3 result = (*this) * m;
	for (size_t i = 0; i < size(); i++)
	{
		for (size_t j = 0; j < size(); j++)
		{
			_column[i][j] = result[i][j];
		}
	}
}

const float& Vec4::operator[](size_t i) const
{
	assert(i < size());
	return (&x)[i];
}

float& Vec4::operator[](size_t i)
{
	assert(i < size());
	return (&x)[i];
}

Mat4::Mat4()
{
	for (size_t i = 0; i < size(); i++)
	{
		for (size_t j = 0; j < size(); j++)
		{
			_column[i][j] = i == j ? 1.0f : 0.0f;
		}
	}
}

Mat4::Mat4(float a00, float a10, float a20, float a30,
		   float a01, float a11, float a21, float a31,
		   float a02, float a12, float a22, float a32,
		   float a03, float a13, float a23, float a33)
{
	_column[0][0] = a00; _column[1][0] = a10; _column[2][0] = a20; _column[3][0] = a30;
	_column[0][1] = a01; _column[1][1] = a11; _column[2][1] = a21; _column[3][1] = a31;
	_column[0][2] = a02; _column[1][2] = a12; _column[2][2] = a22; _column[3][2] = a32;
	_column[0][3] = a03; _column[1][3] = a13; _column[2][3] = a23; _column[3][3] = a33;
}

Mat4::Mat4(Mat3 m)
{
	_column[0][0] = m[0][0]; _column[1][0] = m[1][0]; _column[2][0] = 0.0f; _column[3][0] = m[2][0];
	_column[0][1] = m[0][1]; _column[1][1] = m[1][1]; _column[2][1] = 0.0f; _column[3][1] = m[2][1];
	_column[0][2] = 0.0f;	 _column[1][2] = 0.0f;	  _column[2][2] = 0.0f; _column[3][2] = 0.0f;
	_column[0][3] = 0.0f;	 _column[1][3] = 0.0f;	  _column[2][3] = 0.0;  _column[3][3] = 1.0f;
}

Vec4& Mat4::operator[](size_t i)
{
	assert(i < size());
	return _column[i];
}

const Vec4& Mat4::operator[](size_t i) const
{
	assert(i < size());
	return _column[i];
}


Mat4 Ortho(float const & left,
	float const & right,
	float const & bottom,
	float const & top,
	float const & zNear,
	float const & zFar)
{
	Mat4 Result;
	Result[0][0] = float(2) / (right - left);
	Result[1][1] = float(2) / (top - bottom);
	Result[2][2] = -float(2) / (zFar - zNear);
	Result[3][0] = -(right + left) / (right - left);
	Result[3][1] = -(top + bottom) / (top - bottom);
	Result[3][2] = -(zFar + zNear) / (zFar - zNear);
	return Result;
}

Vec2 operator * (Mat3& m, Vec2& v)
{
	return Vec2(
		m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2],
		m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2],
		m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2]);
}

Mat3 operator * (Mat3& a, Mat3& b)
{
	Mat3 result;
	for (size_t j = 0; j < a.size(); j++)
	{
		for (size_t i = 0; i < b.size(); i++)
		{
			result[i][j] = 0.0f;
			for (size_t r = 0; r < b.size(); r++)
			{
				result[i][j] += a[r][j] * b[i][r];
			}
		}
	}
	return result;
}

bool operator == (Mat3& a, Mat3& b)
{
	for (size_t j = 0; j < a.size(); j++)
	{
		for (size_t i = 0; i < a.size(); i++)
		{
			if (a[i][j] != b[i][j])
				return false;
		}
	}

	return true;
}

bool operator != (Mat3& a, Mat3& b)
{
	return !(a == b);
}

Mat4 operator * (Mat4& a, Mat4& b)
{
	Mat4 result;
	for (size_t j = 0; j < a.size(); j++)
	{
		for (size_t i = 0; i < b.size(); i++)
		{
			result[i][j] = 0.0f;
			for (size_t r = 0; r < b.size(); r++)
			{
				result[i][j] += a[r][j] * b[i][r];
			}
		}
	}
	return result;
}

Mat4 operator * (Mat4& a, Mat3& b)
{
	Mat4 b4(b);
	return a * b4;
}