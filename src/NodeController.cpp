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

Image* NodeController::HandleDrop(const Vector<int>& dropLocation, const char* file)
{
    SDL_Texture* imageTexture = Image::LoadTextureFromFile(file, renderer);
    if (imageTexture)
    {
        Image* image = new Image(dropLocation, imageTexture);
        nodes.emplace_back(image);

        return image;
    }
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

bool NodeController::EmptySelected() const
{
    for (const Node* node : nodes)
    {
        if (node->IsSelected())
        {
            return false;
        }
    }
    return true;
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

void NodeController::UpdateAllNodesTransform(const Vector<int>& graphOffset)
{
    for (Node* node : nodes)
    {
        if (node)
        {
            node->UpdateGlobalTransform(graphOffset);
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

void NodeController::MoveSelectedNodes(const Vector<int>& delta)
{
    for (Node* node : GetSelectedNodes())
    {
        if (node)
        {
            node->Move(delta);
        }
    }
}