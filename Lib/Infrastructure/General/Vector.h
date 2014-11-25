
#pragma once

namespace Infrastructure
{	

template <class T>
class Vector2
{
	public:
		T x;
		T y;

		Vector2(): x(T(0)), y(T(0))
		{
		}

		Vector2(T a, T b) : x(a), y(b)
		{
		}

		Vector2(const Vector2 &source) : x(source.x), y(source.y)
		{
		}

		Vector2& operator= (const Vector2& source)
		{
			x = source.x;
			y = source.y;
			return *this;
		}		
};

template <class T>
class Vector3
{
	public:
		T x;
		T y;
		T z;

		Vector3(): x(T(0)), y(T(0)), z(T(0))
		{
		}

		Vector3(T a, T b, T c) : x(a), y(b), z(c)
		{
		}

		Vector3(const Vector3 &source) : x(source.x), y(source.y), z(source.z)
		{
		}
 
		Vector3& operator= (const Vector3& source)
		{
			x = source.x;
			y = source.y;
			z = source.z;
			return *this;
		}

};

}