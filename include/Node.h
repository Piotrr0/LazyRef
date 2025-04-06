#ifndef NODE_H
#define NODE_H

#include "Vector.h"
#include <SDL2/SDL.h>

class Node
{
public: 
	Node(SDL_Renderer* renderer);
	Node(SDL_Renderer* renderer, const Vector<int>& position);

	virtual void Draw() = 0;

	bool isSelected = false;
	Vector<int> position;

protected:
	SDL_Renderer* renderer;
};

#endif // NODE_H