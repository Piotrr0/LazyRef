#include "LazyWindow.h"
#include "LazyMath.h"
#include <SDL2/SDL.h>

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
    bool running = true;

    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }

            HandleMouseButtonEvents(event.button);
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

void LazyWindow::HandleMouseButtonEvents(const SDL_MouseButtonEvent& event)
{
    if (event.button == SDL_MOUSEBUTTONDOWN) 
    {
        //TODO: Drag
    }
}

void LazyWindow::DrawBackgroundGrid(int size, const SDL_Color& color)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    const int verticalLineCount = LazyMath::CeilToInt((width + size) / size);
    const int horizontalLineCount = LazyMath::CeilToInt((height + size) / size);

    for (int i = 0; i < verticalLineCount; i++)
    {
        SDL_RenderDrawLine(renderer, size * i, -size, size * i, height + size);
    }

    for (int i = 0; i < horizontalLineCount; i++)
    {
        SDL_RenderDrawLine(renderer, -size, size * i, width + size, size * i);
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}
