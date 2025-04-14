#ifndef RECT_H
#define RECT_H

#include "Vector.h"
#include <SDL2/SDL.h>

class Rect
{
public:
	Rect() : topLeft(0, 0), bottomRight(0, 0) {}
	Rect(const Vector<int>& start, const Vector<int>& end);
	Rect(const Vector<int>& position, int width, int height);

	bool Contains(const Vector<int>& point) const;
	bool Intersects(const Rect& rect) const;
	void Resize(const Vector<int>& delta);
	void Resize(int newWidth, int newHeight);
	void SetRect(const Vector<int>& start, const Vector<int>& end);
	void SetRect(const Vector<int>& position, int width, int height);

	int GetWidth() const;
	int GetHeight() const;
	Vector<int> GetAnchor() const;
	Vector<int> GetSize() const;
	Vector<int> GetCenter() const;

	SDL_Rect ConvertSDLRect() const;

protected:
	Vector<int> topLeft{};
	Vector<int> bottomRight{};
};


#endif // !RECT_H
