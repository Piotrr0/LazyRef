#include "Node.h"
#include "Vector.h"
#include "components/Rect.h"

Node::Node(const Vector<int>& position) :
	dropPosition(position)
{

}

Node::Node(const Vector<int>& position, const Vector<int>& offset) :
	dropPosition(position),
	nodeOffset(offset)
{
	worldPosition = position + offset;
}

Vector<int> Node::GetScreenPosition() const
{
	const Vector<int> offsetVector = dropPosition - worldPosition;
	return dropPosition + offsetVector + nodeOffset;
}

Vector<int> Node::GetWorldPosition() const
{
	return dropPosition + nodeOffset;
}

Vector<int> Node::GetSize() const
{
	return Vector<int>(nodeRect.GetWidth() * zoom, nodeRect.GetHeight() * zoom);
}

void Node::ApplyZoom(float zoom)
{
	this->zoom = zoom;

	const float width = baseWidth * zoom;
	const float height = baseHeight * zoom;

	nodeRect.SetRect(worldPosition, width, height);
}
