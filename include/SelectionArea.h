#ifndef SELECTIONAREA_H
#define SELECTIONAREA_H

#include <SDL2/SDL.h>
#include "Vector.h"
#include "components/Rect.h"

class SelectionArea 
{
public:
	SelectionArea(SDL_Renderer* renderer);
	~SelectionArea() {}
	void Draw();

	Vector<int> anchorPoint;
	Vector<int> endPoint;

protected:

	SDL_Renderer* renderer = nullptr;

	Rect areaRect;
	SDL_Rect rectToDraw;
	SDL_Color selectionColor = { 0, 128, 255, 100 }; 
};

#endif // !SELECTIONAREA_H
