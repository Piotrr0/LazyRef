#include "components/Rect.h"
#include "Vector.h"
#include <algorithm>

/*TODO: Add a Min and Max to LazyMath*/
/*TODO: Replace Min and Max from algorithm to LazyMath*/

Rect::Rect(const Vector<int>& start, const Vector<int>& end)
{
	SetRect(start, end);
}

Rect::Rect(const Vector<int>& position, int width, int height)
{
	SetRect(position, width, height);
}


bool Rect::Contains(const Vector<int>& point) const
{
	return (point.x >= topLeft.x && point.x <= bottomRight.x &&
		point.y >= topLeft.y && point.y <= bottomRight.y);
}


bool Rect::Intersects(const Rect& rect) const
{
	return !(rect.topLeft.x > bottomRight.x ||
		rect.bottomRight.x < topLeft.x ||
		rect.topLeft.y > bottomRight.y ||
		rect.bottomRight.y < topLeft.y);
}

void Rect::Resize(const Vector<int>& delta)
{
	const int newWidth = GetWidth() + delta.x;
	const int newHeight = GetHeight() + delta.y;
	Resize(newWidth, newHeight);
}

void Rect::Resize(int newWidth, int newHeight)
{
	bottomRight.x = topLeft.x + newWidth;
	bottomRight.y = topLeft.y + newHeight;

	if (newWidth < 0) std::swap(topLeft.x, bottomRight.x);
	if (newHeight < 0) std::swap(topLeft.y, bottomRight.y);
}

void Rect::SetRect(const Vector<int>& start, const Vector<int>& end)
{
	topLeft.x = std::min(start.x, end.x);
	topLeft.y = std::min(start.y, end.y);
	bottomRight.x = std::max(start.x, end.x);
	bottomRight.y = std::max(start.y, end.y);
}

void Rect::SetRect(const Vector<int>& position, int width, int height)
{
	topLeft = position;
	bottomRight = { position.x + width, position.y + height };

	if (width < 0) std::swap(topLeft.x, bottomRight.x);
	if (height < 0) std::swap(topLeft.y, bottomRight.y);
}

int Rect::GetWidth() const
{
	return bottomRight.x - topLeft.x;
}

int Rect::GetHeight() const
{
	return bottomRight.y - topLeft.y;
}

Vector<int> Rect::GetAnchor() const
{
	return topLeft;
}

Vector<int> Rect::GetSize() const
{
	return { GetWidth(), GetHeight() };
}

Vector<int> Rect::GetCenter() const
{
	return {
		topLeft.x + GetWidth() / 2,
		topLeft.y + GetHeight() / 2
	};
}

SDL_Rect Rect::ConvertSDLRect() const
{
	return {
		topLeft.x,
		topLeft.y,
		GetWidth(),
		GetHeight()
	};
}