#ifndef LAZYWINDOW_H
#define LAZYWINDOW_H

#include <SDL2/SDL.h>
#include "Vector.h"

class SDL_Window;
class SDL_Renderer;

class LazyWindow
{
public:
	LazyWindow(const int width, const int height);
	void StartRendering();

protected:

	void HandleEvents(const SDL_Event& event);
	void HandleQuitEvent(const SDL_Event& event);
	void HandleMouseMotionEvent(const SDL_Event& event);

	void HandleMouseButtonEvents(const SDL_MouseButtonEvent& mouseEvent);
	void HandleMouseButtonDownEvents(const SDL_MouseButtonEvent& mouseEvent);
	void HandleMouseButtonUpEvents(const SDL_MouseButtonEvent& mouseEvent);

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	int gridLargeSize = 50;
	SDL_Color gridLargeColor = SDL_Color{ 255,255,255,102 };

	int gridSmallSize = 25;
	SDL_Color gridSmallColor = SDL_Color{ 255,255,255,51 };

	Vector<int> graphOffset;

	bool running = false;
	bool isDragging = false;

private:

	void DrawBackgroundGrid(int size, const SDL_Color& color);

};

#endif // !LAZYWINDOW_H