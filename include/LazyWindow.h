#ifndef LAZYWINDOW_H
#define LAZYWINDOW_H

#include <SDL2/SDL.h>
#include "Vector.h"

class SDL_Window;
class SDL_Renderer;
class SelectionArea;
class Image;

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
	void HandleDropEvent(const SDL_DropEvent& dropEvent);

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SelectionArea* selectionArea = nullptr;
	Image* droppedImage = nullptr;

	int largeGridSize = 30;
	SDL_Color largeGridColor = SDL_Color{ 255,255,255,102 };

	int smallGridSize = 15;
	SDL_Color smallGridColor = SDL_Color{ 255,255,255,51 };

	float zoom = 1.f;
	float zoomStep = 0.1f;
	float maxZoom = 2.f;
	float minZoom = 0.5f;

	Vector<int> graphOffset;

	bool running = false;
	bool isDragging = false;
	bool isSelecting = false;

private:

	void DrawBackgroundGrid(int size, const SDL_Color& color);
	void DrawSelectionArea();
	void DrawImages();

};

#endif // !LAZYWINDOW_H