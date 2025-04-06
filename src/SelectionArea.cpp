#include "SelectionArea.h"

SelectionArea::SelectionArea(SDL_Renderer* renderer) :
	renderer(renderer)
{

}

void SelectionArea::StartSelecting(const Vector<int>& anchor)
{
	anchorPoint = anchor;
	selectionAreaActive = true;
}

void SelectionArea::StopSelecting()
{
	selectionAreaActive = false;
}

void SelectionArea::Draw() const
{
	if (!selectionAreaActive) return;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, selectionColor.r, selectionColor.g, selectionColor.b, selectionColor.a);

	areaRect.SetRect(anchorPoint, endPoint);

	SDL_Rect rectToDraw = areaRect.ConvertSDLRect();
	SDL_RenderFillRect(renderer, &rectToDraw);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}