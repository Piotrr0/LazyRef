#ifndef SELECTIONAREA_H
#define SELECTIONAREA_H

#include "Vector.h"
#include "components/Rect.h"
#include "Drawable.h"
#include <functional>
#include <unordered_set>

struct SDL_Renderer;
class Node;

class SelectionArea : public Drawable
{
public:
	SelectionArea(SDL_Renderer* renderer);
	~SelectionArea() {}

	void StartSelecting(const Vector<int>& anchor);
	void SetEndPoint(const Vector<int>& endPoint);
	void StopSelecting();

	virtual void Draw(SDL_Renderer* renderer) const override;

	bool selectionAreaActive = false;

	void CheckForSelection(const std::vector<Node*>& nodesToCheck);

	std::function<void(Node*)> onNodeBeginOverlap;
	std::function<void(Node*)> onNodeEndOverlap;

protected:

	Vector<int> anchorPoint;
	Vector<int> endPoint;

	SDL_Renderer* renderer = nullptr;

	SDL_Color selectionColor = { 0, 128, 255, 100 };
	Rect areaRect;

	std::unordered_set<Node*> currentlyOverlappingNodes;
};

#endif // !SELECTIONAREA_H
