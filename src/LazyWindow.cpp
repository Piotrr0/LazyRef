#include "LazyWindow.h"
#include "LazyMath.h"
#include <SDL2/SDL.h>
#include "SelectionArea.h"
#include "Image.h"
#include "Drawable.h"
#include <vector>
#include "NodeController.h"

LazyWindow::LazyWindow(const int width, const int height)
{
	if (width <= 0 || height <= 0)
	{
		window = SDL_CreateWindow
		(
			"LazyRef", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			640, 480,
			SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
		);
	}
	else
	{
		window = SDL_CreateWindow
		(
			"LazyRef", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width, height,
			SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
		);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!renderer)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
		return;
	}

	int currentWidth, currentHeight;
	SDL_GetWindowSize(window, &currentWidth, &currentHeight);

	const int logicalWidth = CalculateLogicalWidth(currentWidth, currentHeight);
	if (renderer != nullptr)
	{
		SDL_RenderSetLogicalSize(renderer, logicalWidth, logicalHeightBase);
	}

	selectionArea = new SelectionArea(renderer);

	selectionArea->onNodeBeginOverlap = [](Node* node)
		{
			node->SetSelected(true);
		};

	selectionArea->onNodeEndOverlap = [](Node* node)
		{
			node->SetSelected(false);
		};

	nodeController = new NodeController(renderer);
}

LazyWindow::~LazyWindow()
{
	if (nodeController)
	{
		delete nodeController;
		nodeController = nullptr;
	}

	if (selectionArea)
	{
		delete selectionArea;
		selectionArea = nullptr;
	}

	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	if (window)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}
}

void LazyWindow::StartRendering()
{
	if (renderer == nullptr) return;
	running = true;

	SDL_Event event;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			HandleEvents(event);
		}

		Tick();

		SDL_SetRenderDrawColor(renderer, 27, 27, 27, 255);
		SDL_RenderClear(renderer);

		DrawDrawable();

		SDL_RenderPresent(renderer);
	}
}

void LazyWindow::HandleEvents(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_QUIT:
		HandleQuitEvent(event);
		break;
	case SDL_DROPFILE:
		HandleDropEvent(event.drop);
		break;
	case SDL_MOUSEMOTION:
		HandleMouseMotionEvent(event.motion);
		break;
	case SDL_MOUSEWHEEL:
		HandleMouseWheelEvent(event.wheel);
		break;
	case SDL_MOUSEBUTTONDOWN:
		HandleMouseButtonDownEvent(event.button);
		break;
	case SDL_MOUSEBUTTONUP:
		HandleMouseButtonUpEvent(event.button);
		break;
	case SDL_WINDOWEVENT:
		HandleWindowEvent(event.window);
		break;
	default:
		break;
	}
}

Vector<int> LazyWindow::MouseToCanvas() const
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	float logicalX, logicalY;
	SDL_RenderWindowToLogical(renderer, x, y, &logicalX, &logicalY);

	return Vector<int>(static_cast<int>(logicalX), static_cast<int>(logicalY));
}

Vector<int> LazyWindow::MouseGlobalToCanvas() const
{
	int mouseX, mouseY;
	SDL_GetGlobalMouseState(&mouseX, &mouseY);

	int windowX, windowY;
	SDL_GetWindowPosition(window, &windowX, &windowY);

	const int relativeX = mouseX - windowX;
	const int relativeY = mouseY - windowY;

	float logicalX, logicalY;
	SDL_RenderWindowToLogical(renderer, relativeX, relativeY, &logicalX, &logicalY);

	return Vector<int>(static_cast<int>(logicalX), static_cast<int>(logicalY));
}

int LazyWindow::CalculateLogicalWidth(float width, float height) const
{
	if (height > 0)
	{
		const float aspectRatio = (float)width / height;
		return static_cast<int>(logicalHeightBase * aspectRatio);
	}
	return 0;
}

void LazyWindow::Tick()
{
	if (nodeController && selectionArea)
	{
		std::vector<Node*> nodes = nodeController->GetNodes();
		selectionArea->CheckForSelection(nodes);
	}
}

Node* LazyWindow::IsMouseOverNode() const
{
	if (!nodeController || nodeController->Empty()) return nullptr;

	if (nodeController)
	{
		return nodeController->GetNodeAtPosition(MouseToCanvas());
	}

	return nullptr;
}

void LazyWindow::HandleWindowEvent(const SDL_WindowEvent& windowEvent)
{
	if (windowEvent.event == SDL_WINDOWEVENT_RESIZED || windowEvent.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		const int newWidth = windowEvent.data1;
		const int newHeight = windowEvent.data2;

		const int logicalWidth = CalculateLogicalWidth(newWidth, newHeight);
		if (renderer)
		{
			SDL_RenderSetLogicalSize(renderer, logicalWidth, logicalHeightBase);
		}
	}
}

void LazyWindow::HandleQuitEvent(const SDL_Event& event)
{
	running = false;
}

void LazyWindow::HandleMouseMotionEvent(const SDL_MouseMotionEvent& motionEvent)
{
	Vector<int> delta = Vector<int>(motionEvent.xrel, motionEvent.yrel);

	if (selectionArea && selectionArea->selectionAreaActive)
	{
		selectionArea->SetEndPoint(Vector(motionEvent.x, motionEvent.y));
	}

	if (nodeController == nullptr) return;

	if (isDragging)
	{
		graphOffset += delta;
	}
	else if (moveSelected)
	{
		nodeController->MoveSelectedNodes(delta);
	}

	nodeController->UpdateAllNodesTransform(graphOffset); // TODO: Not optimal
}

void LazyWindow::HandleMouseWheelEvent(const SDL_MouseWheelEvent& wheelEvent)
{
	// TODO: ZOOM
}

void LazyWindow::HandleMouseButtonDownEvent(const SDL_MouseButtonEvent& mouseEvent)
{
	/*RIGHT MOUSE BUTTON*/
	if (mouseEvent.button == SDL_BUTTON_RIGHT)
	{
		if (nodeController->EmptySelected())
		{
			isDragging = true;
		}
		else
		{
			moveSelected = true;
		}
	}

	/*LEFT MOUSE BUTTON*/
	if (mouseEvent.button == SDL_BUTTON_LEFT)
	{
		const bool ctrl = (SDL_GetModState() & KMOD_CTRL) != 0;
		if (!ctrl)
		{
			nodeController->UnselectAllNodes();
		}

		if (Node* mouseOverNode = IsMouseOverNode())
		{
			if (ctrl)
			{
				mouseOverNode->SetSelected(!mouseOverNode->IsSelected());
			}
			else
			{
				mouseOverNode->SetSelected(true);
			}
		}
		selectionArea->StartSelecting(Vector(mouseEvent.x, mouseEvent.y));
	}
}

void LazyWindow::HandleMouseButtonUpEvent(const SDL_MouseButtonEvent& mouseEvent)
{
	/*RIGHT MOUSE BUTTON*/
	if (mouseEvent.button == SDL_BUTTON_RIGHT)
	{
		isDragging = false;
		moveSelected = false;
	}

	/*LEFT MOUSE BUTTON*/
	if (mouseEvent.button == SDL_BUTTON_LEFT)
	{
		selectionArea->StopSelecting();
	}
}

void LazyWindow::HandleDropEvent(const SDL_DropEvent& dropEvent)
{
	const Vector<int> canvasLocation = MouseGlobalToCanvas();
	const Vector<int> dropLocation = canvasLocation - graphOffset;

	nodeController->HandleDrop(dropLocation, dropEvent.file);
}

void LazyWindow::DrawDrawable() const
{
	const std::vector<Drawable*> objectsToDraw = Drawable::GetAllDrawableObjects();
	for (const Drawable* objectToDraw : objectsToDraw)
	{
		objectToDraw->Draw(renderer);
	}
}