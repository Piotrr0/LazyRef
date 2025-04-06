#include "Node.h"
#include "Vector.h"
#include "LazyWindow.h"

Node::Node(LazyWindow* window) : 
	window(window)
{

}

Node::Node(LazyWindow* window, const Vector<int>& position) :
	window(window),
	position(position)
{

}
