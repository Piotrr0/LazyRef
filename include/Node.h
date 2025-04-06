#ifndef NODE_H
#define NODE_H

#include "Vector.h"
#include "components/Rect.h"
#include "Drawable.h"

class LazyWindow;

class Node : public Drawable
{
public: 
	Node(LazyWindow* window);
	Node(LazyWindow* window, const Vector<int>& position);

	bool isSelected = false;

protected:

	Rect nodeRect;
	Vector<int> position;

	LazyWindow* window;
};

#endif // NODE_H