#ifndef RECT_H
#define RECT_H

#include "Vector.h"

class Rect
{
public:
	Rect(const Vector<int>& start, const Vector<int>& end);
	Rect(Vector<int> position, int width, int height);

	bool Contains(Vector<int> point) const;
	bool Intersects(const Rect* rect) const;

protected:

	Vector<int> topRight;
	Vector<int> topLeft;
	Vector<int> bottomRight;
	Vector<int> bottomLeft;

};


#endif // !RECT_H
