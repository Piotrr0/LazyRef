#include "Node.h"
#include "Vector.h"
#include "components/Rect.h"
#include "LazyWindowProperties.h"

Node::Node(const Vector<int>& position) :
	position(position)
{

}

void Node::Move(const Vector<int>& delta)
{
	position += delta;
	UpdateGlobalTransform(LWProperties::graphOffset);
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