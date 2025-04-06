#ifndef NODE_H
#define NODE_H

#include "Vector.h"
#include <SDL2/SDL.h>

class LazyWindow;

class Node
{
public: 
	Node(LazyWindow* window);
	Node(LazyWindow* window, const Vector<int>& position);

	virtual void Draw(const Vector<int>& graphOffset) = 0;

	bool isSelected = false;
	Vector<int> position;

protected:
	LazyWindow* window;
};

#endif // NODE_H