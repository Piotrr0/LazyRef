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

	void ApplyZoom(float zoom);
	void ApplyOffset(const Vector<int>& offset);
	void RefreshTransform();
	void UpdateTransform(const Vector<int>& size, const Vector<int>& position);

	virtual void SetSelected(bool isSelected) { this->isSelected = isSelected; }
	bool IsSelected() const { return isSelected; }

	int GetBaseWidth() const { return baseWidth; }
	int GetBaseHeight() const { return baseHeight; }

protected:
	int baseWidth = 0;
	int baseHeight = 0;

	Vector<int> dropPosition;
	Rect nodeRect;

	Vector<int> nodeOffset;
	float zoom = 1.f;

	bool isSelected = false;
};

#endif // NODE_H