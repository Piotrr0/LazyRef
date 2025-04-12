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

}

void Node::ApplyZoom(float zoom)
{
	this->zoom = zoom;
	RefreshTransform();
}

void Node::ApplyOffset(const Vector<int>& offset)
{
	this->nodeOffset = offset;
	RefreshTransform();
}

void Node::RefreshTransform()
{
	const Vector<int> effectiveSize(baseWidth * zoom, baseHeight * zoom);
	const Vector<int> effectivePosition = dropPosition + nodeOffset;

	UpdateTransform(effectiveSize, effectivePosition);
}

void Node::UpdateTransform(const Vector<int>& size, const Vector<int>& position)
{
	nodeRect.SetRect(position, size.x, size.y);
}