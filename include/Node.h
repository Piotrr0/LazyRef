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

	Vector<int> GetScreenPosition() const;
	Vector<int> GetSize() const;

protected:

	Rect nodeRect;

	Vector<int> worldPosition;
	Vector<int> dropPosition;

	LazyWindow* window;
};

#endif // NODE_H