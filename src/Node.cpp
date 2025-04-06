#include "Node.h"
#include "Vector.h"
#include <SDL2/SDL.h>

Node::Node(SDL_Renderer* renderer) : 
	renderer(renderer)
{

}

Node::Node(SDL_Renderer* renderer, const Vector<int>& position) :
	renderer(renderer),
	position(position)
{

}
