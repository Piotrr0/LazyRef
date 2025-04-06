#include "Node.h"
#include "Vector.h"
#include "LazyWindow.h"

Node::Node(LazyWindow* window) : 
	window(window)
{

}

Node::Node(LazyWindow* window, const Vector<int>& position) :
	window(window),
	dropPosition(position)
{
	worldPosition = dropPosition + window->GetGraphOffset();
}

Vector<int> Node::GetScreenPosition() const
{
	const Vector<int> offsetVector = dropPosition - worldPosition;
	return dropPosition + offsetVector + window->GetGraphOffset();
}

Vector<int> Node::GetSize() const
{
	const float zoom = window->GetZoom();
	return Vector<int>(nodeRect.GetWidth() * zoom, nodeRect.GetHeight() * zoom);
}
