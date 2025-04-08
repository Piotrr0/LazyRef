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

	Vector<int> GetScreenPosition() const;
	Vector<int> GetWorldPosition() const;

	Vector<int> GetSize() const;
	Vector<float> GetScale() const { return scale; }
	Rect GetRect() const { return nodeRect; }

	void SetOffset(const Vector<int>& offset) { nodeOffset = offset; }
	void SetScale(const Vector<float>& scale) { this->scale = scale; }
	virtual void SetSelected(bool isSelected) { this->isSelected = isSelected; }

	float zoom = 1.f; // TODO: DO IT DIFFRENTLY USING ONLY SCALE VECTOR

protected:

	mutable Rect nodeRect;

	Vector<int> nodeOffset;
	Vector<float> scale = Vector(1.f, 1.f);


	Vector<int> worldPosition;
	Vector<int> dropPosition;
};

#endif // NODE_H