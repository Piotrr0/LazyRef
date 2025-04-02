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
	void HandleMouseMotionEvent(const SDL_MouseMotionEvent& motionEvent);
	void HandleMouseWheelEvent(const SDL_MouseWheelEvent& wheelEvent);
	void HandleMouseButtonDownEvent(const SDL_MouseButtonEvent& mouseEvent);
	void HandleMouseButtonUpEvent(const SDL_MouseButtonEvent& mouseEvent);

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	int gridSize = 25;
	SDL_Color gridColor = SDL_Color{ 255,255,255,102 };

	float zoom = 1.f;
	float maxZoom = 2.f;
	float minZoom = 0.5f;

	Vector<int> graphOffset;

	bool running = false;
	bool isDragging = false;

private:

	void DrawBackgroundGrid(int size, const SDL_Color& color);

};

#endif // !LAZYWINDOW_H