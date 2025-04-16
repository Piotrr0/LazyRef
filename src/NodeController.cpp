#include "NodeController.h"
#include "Image.h"
#include "Vector.h"
#include "Node.h"
#include <SDL2/SDL.h>
#include <vector>

NodeController::NodeController(SDL_Renderer* renderer)
    : renderer(renderer)
{

}

Image* NodeController::HandleDropEvent(const SDL_DropEvent& dropEvent, const Vector<int>& graphOffset, SDL_Window* window)
{
    if (dropEvent.file)
    {
        int mouseX, mouseY;
        SDL_GetGlobalMouseState(&mouseX, &mouseY);

        int windowX, windowY;
        SDL_GetWindowPosition(window, &windowX, &windowY);

        const int relativeX = mouseX - windowX;
        const int relativeY = mouseY - windowY;

        float logicalX, logicalY;
        SDL_RenderWindowToLogical(renderer, relativeX, relativeY, &logicalX, &logicalY);

        Vector<int> dropLocation(static_cast<int>(logicalX), static_cast<int>(logicalY));

        SDL_Texture* imageTexture = Image::LoadTextureFromFile(dropEvent.file, renderer);
        if (imageTexture)
        {
            Image* image = new Image(dropLocation, Vector<int>(0, 0), imageTexture);
            image->UpdateGlobalTransform(currentZoom, graphOffset);
            nodes.emplace_back(image);

            SDL_free(dropEvent.file);
            return image;
        }

        SDL_free(dropEvent.file);
    }

    return nullptr;
}

std::vector<Node*> NodeController::GetSelectedNodes() const
{
    std::vector<Node*> selectedNodes;
    for (Node* node : nodes)
    {
        if (node->IsSelected())
        {
            selectedNodes.emplace_back(node);
        }
    }
    return selectedNodes;
}

Node* NodeController::GetNodeAtPosition(const Vector<int>& position) const
{
    for (auto it = nodes.rbegin(); it != nodes.rend(); ++it)
    {
        Node* node = *it;
        if (node && node->GetRect().Contains(position))
        {
            return node;
        }
    }
    return nullptr;
}

void NodeController::UpdateAllNodesTransform(float zoom, const Vector<int>& offset)
{
    for (Node* node : nodes)
    {
        if (node)
        {
            node->UpdateGlobalTransform(zoom, offset);
        }
    }
}

void NodeController::UnselectAllNodes()
{
    for (Node* node : nodes)
    {
        if (node)
        {
            node->SetSelected(false);
        }
    }
}
