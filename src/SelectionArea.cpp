#include "SelectionArea.h"

SelectionArea::SelectionArea(SDL_Renderer* renderer, const Vector<int>& anchorPoint) :
	renderer(renderer),
	anchorPoint(anchorPoint),
	areaRect(anchorPoint, 0, 0)
{
	rectToDraw = areaRect.ConvertSDLRect();
	endPoint = this->anchorPoint;
}

void SelectionArea::Draw()
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, selectionColor.r, selectionColor.g, selectionColor.b, selectionColor.a);

	areaRect.SetRect(anchorPoint, endPoint);
	rectToDraw = areaRect.ConvertSDLRect();

	SDL_RenderFillRect(renderer, &rectToDraw);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}
