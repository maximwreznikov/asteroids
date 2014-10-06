#ifndef Math_h
#define Math_h

#include <math.h>
#include <assert.h>

struct Vec2
{
	Vec2() { x = 0.0f; y = 0.0f; w = 1.0f; }
	Vec2(float x_, float y_, float w_ = 1.0f) : x(x_), y(y_), w(w_) {}

	size_t size() const
	{
		return 3;
	}

	void Set(float x_, float y_) { x = x_; y = y_; }

	float& operator[](size_t i);

	Vec2 operator -() { return Vec2(-x, -y); }

	void operator += (const Vec2& v)
	{
		x += v.x; y += v.y;
	}

	void operator -= (const Vec2& v)
	{
		x -= v.x; y -= v.y;
	}

	void operator *= (float a)
	{
		x *= a; y *= a;
	}
	void operator /= (float a)
	{
		x /= a; y /= a;
	}

	float Length() const
	{
		return sqrtf(x * x + y * y);
	}

	union
	{
		struct{ float x, y, w; };
	};
};

struct Mat3
{
	Mat3();
	Mat3(float angle, Vec2 translate_ = Vec2());
	Mat3(float a, float b, float c, float d, float tx = 0.0f, float ty = 0.0f, float w = 1.0f);

	size_t size() const
	{
		return 3;
	}

	void Translate(Vec2 v)
	{
		_column[2][0] += v.x;
		_column[2][1] += v.y;
	}

	void Rotate(float angle)
	{
		Mat3 rotate(angle);
		(*this) *= rotate;
	}

	void operator *= (Mat3 m);

	Vec2& operator[](size_t i);
private:
	Vec2  _column[3];
};

struct Vec4
{
	float& operator[](size_t i);
	const float& operator[](size_t i) const;
	size_t size() const
	{
		return 4;
	}
	union
	{
		struct{ float r, g, b, a; };
		struct{ float x, y, z, w; };
	};
};

struct Mat4
{
	Mat4();
	Mat4(float a00, float a10, float a20, float a30,
		float a01, float a11, float a21, float a31,
		float a02, float a12, float a22, float a32,
		float a03, float a13, float a23, float a33);
	Mat4(Mat3 m);

	size_t size() const
	{
		return 4;
	}

	Vec4& operator[](size_t i);
	const Vec4& operator[](size_t i) const;
private:
	Vec4 _column[4];
};

Vec2 operator * (Mat3& m, Vec2& v);

Mat3 operator * (Mat3& a, Mat3& b);

bool operator == (Mat3& a, Mat3& b);

bool operator != (Mat3& a, Mat3& b);

Mat4 operator * (Mat4& a, Mat4& b);

Mat4 operator * (Mat4& a, Mat3& b);

/**
@brief Ортографическая проекция
*/
Mat4 Ortho(float const & left, 
		   float const & right,
		   float const & bottom,
		   float const & top,
	       float const & zNear,
		   float const & zFar);

inline Vec2 operator * (const Vec2& v, float a)
{
	return Vec2(v.x * a, v.y * a);
}

inline Vec2 operator * (float a, const Vec2& v)
{
	return Vec2(a * v.x, a * v.y);
}

inline Vec2 operator / (const Vec2& v, float a)
{
	return Vec2(v.x / a, v.y / a);
}

inline Vec2 operator + (const Vec2& v1, const Vec2& v2)
{
	return Vec2(v1.x + v2.x, v1.y + v2.y);
}

inline Vec2 operator - (const Vec2& v1, const Vec2& v2)
{
	return Vec2(v1.x - v2.x, v1.y - v2.y);
}

inline float Length(const Vec2& v)
{
	return sqrtf(v.x * v.x + v.y * v.y);
}

inline Vec2 Normalize(const Vec2& a)
{
	float l = Length(a);
	return a / l;
}

inline float Distance(const Vec2& a, const Vec2& b)
{
	return Length(a - b);
}

inline float Dot(const Vec2& a, const Vec2& b)
{
	return a.x * b.x + a.y * b.y;
}

inline float Cross(const Vec2& a, const Vec2& b)
{
	return a.x * b.y - a.y * b.x;
}

inline float Min(float a, float b)
{
	return a < b ? a : b;
}

inline float Max(float a, float b)
{
	return a > b ? a : b;
}

inline float Middle(float a, float low, float high)
{
	return Max(low, Min(a, high));
}

//правая нормаль
inline Vec2 RightNormal(const Vec2& a, float s)
{
	return Vec2(s * a.y, -s * a.x);
}

//левая нормаль
inline Vec2 LeftNormal(float s, const Vec2& a)
{
	return Vec2(-s * a.y, s * a.x);
}

#endif