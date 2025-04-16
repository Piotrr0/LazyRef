#ifndef NODE_H
#define NODE_H

#include "Vector.h"
#include "components/Rect.h"
#include "Drawable.h"

class Node : public Drawable
{
public:
	Node(const Vector<int>& position);
	Node(const Vector<int>& position, const Vector<int>& offset);
	virtual ~Node() = default;

	Rect GetRect() const { return nodeRect; }
	void Move(const Vector<int>& delta);
	void UpdateTransform(const Vector<int>& size, const Vector<int>& position);

	virtual void SetSelected(bool isSelected) { this->isSelected = isSelected; }
	bool IsSelected() const { return isSelected; }

	int GetBaseWidth() const { return baseWidth; }
	int GetBaseHeight() const { return baseHeight; }

	void UpdateGlobalTransform(const Vector<int>& globalOffset);

protected:
	int baseWidth = 0;
	int baseHeight = 0;

	Vector<int> position;
	Rect nodeRect;

	Vector<int> nodeOffset;

	bool isSelected = false;
};

#endif // NODE_H