#ifndef RECT_H
#define RECT_H

#include "Vector.h"

class Rect
{
public:
	Rect(const Vector<int>& start, const Vector<int>& end);
	Rect(const Vector<int>& position, int width, int height);

	bool Contains(const Vector<int>& point) const;
	bool Intersects(const Rect* rect) const;
	void Resize(const Vector<int>& delta);
	void SetRect(const Vector<int>& start, const Vector<int>& end);
	void SetRect(const Vector<int>& position, int width, int height);

	int GetWidth() const;
	int GetHeight() const;
protected:

	Vector<int> topRight{};
	Vector<int> topLeft{};
	Vector<int> bottomRight{};
	Vector<int> bottomLeft{};

};


#endif // !RECT_H
