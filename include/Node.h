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

	bool isSelected = false;

	Rect GetRect() const { return nodeRect; }

	void ApplyZoom(float zoom);
	void ApplyOffset(const Vector<int>& offset);
	void RefreshTransform();
	void UpdateTransform(const Vector<int>& size, const Vector<int>& position);

	virtual void SetSelected(bool isSelected) { this->isSelected = isSelected; }

	float baseWidth = 0.f;
	float baseHeight = 0.f;

protected:

	Rect nodeRect;

	Vector<int> nodeOffset;
	float zoom = 1.f;

	Vector<int> dropPosition;
};

#endif // NODE_H