#include "components/Rect.h"
#include <algorithm>

Rect::Rect(const Vector<int>& start, const Vector<int>& end)
{
	topLeft.x = std::min(start.x, end.x);
	topLeft.y = std::min(start.y, end.y);

	bottomRight.x = std::max(start.x, end.x);
	bottomRight.y = std::max(start.y, end.y);

	topRight = { bottomRight.x, topLeft.y };
	bottomLeft = { topLeft.x, bottomRight.y };
}

Rect::Rect(Vector<int> position, int width, int height)
{
	topLeft = position;
	topRight = { position.x + width, position.y };
	bottomLeft = { position.x, position.y + height };
	bottomRight = { position.x + width, position.y + height };
}

bool Rect::Contains(Vector<int> point) const
{
	return (point.x >= topLeft.x && point.x <= topRight.x &&
		point.y >= topLeft.y && point.y <= bottomLeft.y);
}

bool Rect::Intersects(const Rect* rect) const
{
	if (rect->Contains(topLeft)) return true;
	if (rect->Contains(topRight)) return true;
	if (rect->Contains(bottomLeft)) return true;
	if (rect->Contains(bottomRight)) return true;

	return false;
}
