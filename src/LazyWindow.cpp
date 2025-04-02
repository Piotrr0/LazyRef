#include "LazyWindow.h"
#include "LazyMath.h"
#include <SDL2/SDL.h>
#include <iostream>

LazyWindow::LazyWindow(const int width, const int height)
{
	window = SDL_CreateWindow(
		"LazyRef",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void LazyWindow::StartRendering()
{
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

		DrawBackgroundGrid(gridSmallSize, gridSmallColor);
		DrawBackgroundGrid(gridLargeSize, gridLargeColor);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void LazyWindow::HandleEvents(const SDL_Event& event)
{
	HandleQuitEvent(event);
	HandleMouseMotionEvent(event);
	HandleMouseButtonEvents(event.button);
}

void LazyWindow::HandleQuitEvent(const SDL_Event& event)
{
	if (event.type == SDL_QUIT)
	{
		running = false;
	}
}

void LazyWindow::HandleMouseMotionEvent(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEMOTION)
	{
		if (isDragging)
		{
			graphOffset.x += event.motion.xrel;
			graphOffset.y += event.motion.yrel;
		}
	}
}

void LazyWindow::HandleMouseButtonEvents(const SDL_MouseButtonEvent& mouseEvent)
{
	if (mouseEvent.type == SDL_MOUSEBUTTONDOWN)
	{
		HandleMouseButtonDownEvents(mouseEvent);
	}
	else if (mouseEvent.type == SDL_MOUSEBUTTONUP)
	{
		HandleMouseButtonUpEvents(mouseEvent);
	}
}

void LazyWindow::HandleMouseButtonDownEvents(const SDL_MouseButtonEvent& mouseEvent)
{
	if (mouseEvent.button == SDL_BUTTON_RIGHT)
	{
		isDragging = true;
	}
}

void LazyWindow::HandleMouseButtonUpEvents(const SDL_MouseButtonEvent& mouseEvent)
{
	if (mouseEvent.button == SDL_BUTTON_RIGHT)
	{
		isDragging = false;
	}
}

void LazyWindow::DrawBackgroundGrid(int size, const SDL_Color& color)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	int width, height;
	SDL_GetWindowSize(window, &width, &height);

	const Vector<int> gridRenderOffset((graphOffset.x / 2) % size, (graphOffset.y / 2) % size);

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
