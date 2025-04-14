#include "LazyWindow.h"
#include "LazyMath.h"
#include <SDL2/SDL.h>
#include "SelectionArea.h"
#include "Image.h"
#include "Drawable.h"
#include <vector>

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

	if (currentHeight > 0) 
	{
		const float aspectRatio = (float)currentWidth / currentHeight;
		const int logicalWidth = static_cast<int>(logicalHeightBase * aspectRatio);
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

		SDL_SetRenderDrawColor(renderer, 27,27,27,255);
		SDL_RenderClear(renderer);

		DrawDrawable();

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
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

void LazyWindow::Tick()
{
	if (Node* mouseOverNode = IsMouseOverNode())
	{
		//TODO:
	}

	if (droppedImage != nullptr)
	{
		selectionArea->CheckForSelection({droppedImage});
	}
}

Node* LazyWindow::IsMouseOverNode() const
{
	if (droppedImage != nullptr)
	{
		Vector<float> logicalMousePos = GetGlobalToLogicalPosition();
		if (droppedImage->GetRect().Contains(Vector<int>(static_cast<int>(logicalMousePos.x), static_cast<int>(logicalMousePos.y))))
		{
			return droppedImage;
		}
	}
	return nullptr;
}

void LazyWindow::HandleWindowEvent(const SDL_WindowEvent& windowEvent)
{
	if (windowEvent.event == SDL_WINDOWEVENT_RESIZED || windowEvent.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		const int newWidth = windowEvent.data1;
		const int newHeight = windowEvent.data2;

		if (newHeight > 0 && renderer)
		{
			const float newAspectRatio = (float)newWidth / newHeight;
			const int newLogicalWidth = static_cast<int>(logicalHeightBase * newAspectRatio);
			SDL_RenderSetLogicalSize(renderer, newLogicalWidth, logicalHeightBase);
		}
	}
}

void LazyWindow::HandleQuitEvent(const SDL_Event& event)
{
	running = false;
}

void LazyWindow::HandleMouseMotionEvent(const SDL_MouseMotionEvent& motionEvent)
{
	if (isDragging)
	{
		graphDrag = Vector(motionEvent.xrel, motionEvent.yrel);
		graphOffset += graphDrag;

		if (droppedImage)
		{
			droppedImage->ApplyOffset(graphOffset);
		}
	}

	if (selectionArea && selectionArea->selectionAreaActive)
	{
		selectionArea->SetEndPoint(Vector(motionEvent.x, motionEvent.y));
	}
}

void LazyWindow::HandleMouseWheelEvent(const SDL_MouseWheelEvent& wheelEvent)
{
	zoom = LazyMath::Clamp(zoom + wheelEvent.preciseY * zoomStep, minZoom, maxZoom);
	if (droppedImage != nullptr)
	{
		droppedImage->ApplyZoom(zoom);
	}
}

void LazyWindow::HandleMouseButtonDownEvent(const SDL_MouseButtonEvent& mouseEvent)
{
	/*RIGHT MOUSE BUTTON*/
	if (mouseEvent.button == SDL_BUTTON_RIGHT)
	{
		isDragging = true;
	}

	/*LEFT MOUSE BUTTON*/
	if (mouseEvent.button == SDL_BUTTON_LEFT)
	{
		selectionArea->StartSelecting(Vector(mouseEvent.x, mouseEvent.y));
	}
}

void LazyWindow::HandleMouseButtonUpEvent(const SDL_MouseButtonEvent& mouseEvent)
{
	/*RIGHT MOUSE BUTTON*/
	if (mouseEvent.button == SDL_BUTTON_RIGHT)
	{
		isDragging = false;
	}

	/*LEFT MOUSE BUTTON*/
	if (mouseEvent.button == SDL_BUTTON_LEFT)
	{
		selectionArea->StopSelecting();
	}
}

void LazyWindow::HandleDropEvent(const SDL_DropEvent& dropEvent)
{
	if (dropEvent.file)
	{
		if (droppedImage != nullptr)
		{
			delete droppedImage;
			droppedImage = nullptr;
		}

		const Vector<float> dropLocation = GetGlobalToLogicalPosition();
		const Vector<int> logicalPosition = Vector<int>(static_cast<int>(dropLocation.x), static_cast<int>(dropLocation.y));

		SDL_Texture* image = Image::LoadTextureFromFile(dropEvent.file, renderer);

		droppedImage = new Image(logicalPosition, graphOffset ,image);

		SDL_free(dropEvent.file);
	}
}

void LazyWindow::DrawDrawable() const
{
	const std::vector<Drawable*> objectsToDraw = Drawable::GetAllDrawableObjects();
	for (const Drawable* objectToDraw : objectsToDraw)
	{
		objectToDraw->Draw(renderer);
	}
}

Vector<float> LazyWindow::GetGlobalToLogicalPosition() const
{
	int mouseX, mouseY;
	SDL_GetGlobalMouseState(&mouseX, &mouseY);

	int windowX, windowY;
	SDL_GetWindowPosition(window, &windowX, &windowY);

	const int relativeX = mouseX - windowX;
	const int relativeY = mouseY - windowY;

	float logicalX, logicalY;
	SDL_RenderWindowToLogical(renderer, relativeX, relativeY, &logicalX, &logicalY);

	return Vector<float>(logicalX, logicalY);
}