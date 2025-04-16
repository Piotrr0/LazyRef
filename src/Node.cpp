#include "Node.h"
#include "Vector.h"
#include "components/Rect.h"

Node::Node(const Vector<int>& position) :
	position(position)
{

}

Node::Node(const Vector<int>& position, const Vector<int>& offset) :
	position(position),
	nodeOffset(offset)
{

}

void Node::Move(const Vector<int>& delta)
{
	position += delta;
}

void Node::UpdateTransform(const Vector<int>& size, const Vector<int>& position)
{
	nodeRect.SetRect(position, size.x, size.y);
}

void Node::UpdateGlobalTransform(const Vector<int>& globalOffset)
{
	this->nodeOffset = globalOffset;

	const Vector<int> effectiveSize(baseWidth, baseHeight);
	const Vector<int> effectivePosition = position + globalOffset;

	UpdateTransform(effectiveSize, effectivePosition);
}