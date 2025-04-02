#ifndef LAZYWINDOW_H
#define LAZYWINDOW_H

#include <SDL2/SDL.h>

class SDL_Window;
class SDL_Renderer;

class LazyWindow
{
public:
	LazyWindow(const int width, const int height);
	void StartRendering();

protected:

	void HandleMouseButtonEvents(const SDL_MouseButtonEvent& mouseEvent);

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	int gridLargeSize = 50;
	SDL_Color gridLargeColor = SDL_Color{ 255,255,255,102 };

	int gridSmallSize = 25;
	SDL_Color gridSmallColor = SDL_Color{ 255,255,255,51 };

	bool running = false;

private:

	void DrawBackgroundGrid(int size, const SDL_Color& color);

};

#endif // !LAZYWINDOW_H