#include "LazyWindow.h"
#include "LazyMath.h"
#include <SDL2/SDL.h>
#include "SelectionArea.h"

LazyWindow::LazyWindow(const int width, const int height)
{
	window = SDL_CreateWindow(
		"LazyRef",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	selectionArea = new SelectionArea(renderer);
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

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		DrawBackgroundGrid(gridSize * zoom, gridColor);
		DrawSelectionArea();

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
	default:
		break;
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
		graphOffset = Vector(motionEvent.xrel, motionEvent.yrel);
	}

	if (isSelecting)
	{
		selectionArea->endPoint = Vector(motionEvent.x, motionEvent.y);
	}
}

void LazyWindow::HandleMouseWheelEvent(const SDL_MouseWheelEvent& wheelEvent)
{
	zoom = LazyMath::Clamp(zoom + wheelEvent.preciseY * zoomStep, minZoom, maxZoom);
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
		isSelecting = true;
		selectionArea->anchorPoint = Vector(mouseEvent.x, mouseEvent.y);
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
		isSelecting = false;
	}
}

void LazyWindow::DrawBackgroundGrid(int size, const SDL_Color& color)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	int width, height;
	SDL_GetWindowSize(window, &width, &height);

	const Vector<int> gridRenderOffset(graphOffset.x % size, graphOffset.y % size);

	const int verticalLineCount = LazyMath::CeilToInt((width + size) / size);
	const int horizontalLineCount = LazyMath::CeilToInt((height + size) / size);

	for (int i = 0; i < verticalLineCount; i++)
	{
		SDL_RenderDrawLine(renderer, (size * i) + gridRenderOffset.x, (-size) + gridRenderOffset.y, (size * i) + gridRenderOffset.x, (height + size) + gridRenderOffset.y);
	}

	for (int i = 0; i < horizontalLineCount; i++)
	{
		SDL_RenderDrawLine(renderer, (-size) + gridRenderOffset.x, (size * i) + gridRenderOffset.y, (width + size) + gridRenderOffset.x, (size * i) + gridRenderOffset.y);
	}
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

void LazyWindow::DrawSelectionArea()
{
	if (isSelecting)
	{
		selectionArea->Draw();
	}
}