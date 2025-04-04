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
	return (point.x >= topLeft.x && point.x <= topRight.x &&
		point.y >= topLeft.y && point.y <= bottomLeft.y);
}

bool Rect::Intersects(const Rect* rect) const
{
	return !(rect->topLeft.x > bottomRight.x ||
		rect->bottomRight.x < topLeft.x ||
		rect->topLeft.y > bottomRight.y ||
		rect->bottomRight.y < topLeft.y);
}

void Rect::Resize(const Vector<int>& delta)
{
	const int newWidth = GetWidth() + delta.x;
	const int newHeight = GetHeight() + delta.y;

	const int newLeft = topLeft.x;
	const int newTop = topLeft.y;
	const int newRight = topLeft.x + newWidth;
	const int newBottom = topLeft.y + newHeight;

	const Vector<int> newTopLeft = { std::min(newLeft, newRight), std::min(newTop, newBottom) };
	const Vector<int> newBottomRight = { std::max(newLeft, newRight), std::max(newTop, newBottom) };

	const Vector<int> newTopRight = { newBottomRight.x, newTopLeft.y };
	const Vector<int> newBottomLeft = { newTopLeft.x, newBottomRight.y };

	topLeft = newTopLeft;
	topRight = newTopRight;
	bottomLeft = newBottomLeft;
	bottomRight = newBottomRight;
}

void Rect::SetRect(const Vector<int>& start, const Vector<int>& end)
{
	topLeft.x = std::min(start.x, end.x);
	topLeft.y = std::min(start.y, end.y);

	bottomRight.x = std::max(start.x, end.x);
	bottomRight.y = std::max(start.y, end.y);

	topRight = { bottomRight.x, topLeft.y };
	bottomLeft = { topLeft.x, bottomRight.y };
}

void Rect::SetRect(const Vector<int>& position, int width, int height)
{
	topLeft = position;
	topRight = { position.x + width, position.y };
	bottomLeft = { position.x, position.y + height };
	bottomRight = { position.x + width, position.y + height };
}

int Rect::GetWidth() const
{
	return topRight.x - topLeft.x;
}

int Rect::GetHeight() const
{
	return bottomLeft.y - topLeft.y;
}
