#ifndef NODECONTROLLER_H
#define NODECONTROLLER_H

#include <vector>
#include <SDL2/SDL.h>
#include "Vector.h"

class Node;
class Image;

class NodeController
{
public:
	NodeController(SDL_Renderer* renderer);
	Image* HandleDropEvent(const SDL_DropEvent& dropEvent, const Vector<int>& graphOffset, SDL_Window* window);

	std::vector<Node*> GetNodes() const { return nodes; }
	bool Empty() const { return nodes.empty(); }

	Node* GetNodeAtPosition(const Vector<int>& position) const;
	void UpdateAllNodesTransform(float zoom, const Vector<int>& offset);

protected:
	SDL_Renderer* renderer;
	std::vector<Node*> nodes;

	float currentZoom = 1.f;
};

#endif