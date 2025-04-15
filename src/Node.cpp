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

void Node::UpdateTransform(const Vector<int>& size, const Vector<int>& position)
{
	nodeRect.SetRect(position, size.x, size.y);
}

void Node::UpdateGlobalTransform(float globalZoom, const Vector<int>& globalOffset)
{
	this->zoom = globalZoom;
	this->nodeOffset = globalOffset;

	const Vector<int> effectiveSize(baseWidth * globalZoom, baseHeight * globalZoom);
	const Vector<int> effectivePosition = dropPosition + globalOffset;

	UpdateTransform(effectiveSize, effectivePosition);
}
