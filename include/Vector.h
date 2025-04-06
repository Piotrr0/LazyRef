#ifndef VECTOR_H
#define VECTOR_H

template<class T>
class Vector
{
public:
	Vector();
	Vector(T x, T y);

	T x;
	T y;

	Vector operator+(const Vector& other) const
	{
		return Vector(x + other.x, y + other.y);
	}

	Vector operator-(const Vector& other) const
	{
		return Vector(x - other.x, y - other.y);
	}

	Vector operator*(float value) const
	{
		return Vector(x * value, y * value);
	}

	Vector& operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector& operator*=(const Vector& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}
};

template<class T>
Vector<T>::Vector() : x(0), y(0)
{

}

template<class T>
Vector<T>::Vector(T x, T y) : x(x), y(y) 
{

}
#endif // VECTOR_H