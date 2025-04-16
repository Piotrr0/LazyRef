#include "SelectionArea.h"
#include <SDL2/SDL.h>
#include "Node.h"
#include <vector>

//TODO: THIS SHOULD WORK ONLY USING RECT

SelectionArea::SelectionArea(SDL_Renderer* renderer) :
	renderer(renderer)
{

}

void SelectionArea::StartSelecting(const Vector<int>& anchor)
{
	anchorPoint = anchor;
	selectionAreaActive = true;
}

void SelectionArea::SetEndPoint(const Vector<int>& endPoint)
{
    this->endPoint = endPoint;
    areaRect.SetRect(anchorPoint, this->endPoint);
}

void SelectionArea::StopSelecting()
{
	selectionAreaActive = false;

	anchorPoint = Vector(0,0);
	endPoint = Vector(0, 0);
    areaRect.SetRect(anchorPoint, endPoint);
    currentlyOverlappingNodes.clear();
}

void SelectionArea::Draw(SDL_Renderer* renderer) const
{
	if (!selectionAreaActive) return;

	SDL_Rect rectToDraw = areaRect.ConvertSDLRect();

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, selectionColor.r, selectionColor.g, selectionColor.b, selectionColor.a);
	SDL_RenderFillRect(renderer, &rectToDraw);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

void SelectionArea::CheckForSelection(const std::vector<Node*>& nodesToCheck)
{
    if (!selectionAreaActive) return;

    std::unordered_set<Node*> nodesThisFrame;

    for (Node* node : nodesToCheck)
    {
        if (!node) continue;

        const Rect& nodeRect = node->GetRect();

        if (areaRect.Intersects(nodeRect))
        {
            nodesThisFrame.insert(node);

            if (currentlyOverlappingNodes.find(node) == currentlyOverlappingNodes.end())
            {
                if (onNodeBeginOverlap)
                {
                    onNodeBeginOverlap(node);
                }
            }
        }
    }

    for (Node* node : currentlyOverlappingNodes)
    {
        if (nodesThisFrame.find(node) == nodesThisFrame.end())
        {
            if (onNodeEndOverlap)
            {
                onNodeEndOverlap(node);
            }
        }
    }

    currentlyOverlappingNodes = nodesThisFrame;
}