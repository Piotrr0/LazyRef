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
            Image* image = new Image(dropLocation, graphOffset, imageTexture);
            nodes.emplace_back(image);

            SDL_free(dropEvent.file);
            return image;
        }

        SDL_free(dropEvent.file);
    }

    return nullptr;
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

void NodeController::ApplyOffsetToAllNodes(const Vector<int>& offset)
{
    for (Node* node : nodes)
    {
        if (node)
        {
            node->ApplyOffset(offset);
        }
    }
}

void NodeController::ApplyZoomToAllNodes(float zoom)
{
    for (Node* node : nodes)
    {
        if (node)
        {
            node->ApplyZoom(zoom);
        }
    }
}