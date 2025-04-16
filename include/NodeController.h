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
	Image* HandleDrop(const Vector<int>& dropLocation, const char* file);

	std::vector<Node*> GetNodes() const { return nodes; }
	std::vector<Node*> GetSelectedNodes() const;

	bool Empty() const { return nodes.empty(); }
	bool EmptySelected() const; // TODO: Not optimal can we write more optimized

	Node* GetNodeAtPosition(const Vector<int>& position) const;
	void UpdateAllNodesTransform(const Vector<int>& offset);
	void UnselectAllNodes();
	void MoveSelectedNodes(const Vector<int>& delta);


protected:
	SDL_Renderer* renderer;
	std::vector<Node*> nodes;

	float currentZoom = 1.f;
};

#endif