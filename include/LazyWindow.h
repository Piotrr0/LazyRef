#ifndef LAZYWINDOW_H
#define LAZYWINDOW_H

#include <SDL2/SDL.h>
#include "Vector.h"

class SelectionArea;
class Image;

class LazyWindow
{
public:
	LazyWindow(const int width, const int height);
	void StartRendering();

	SDL_Renderer* GetRenderer() const { return renderer; }
	float GetZoom() const { return zoom; }
	Vector<int> GetGraphOffset() const { return graphOffset; }
	Vector<int> GetGraphDrag() const { return graphDrag; }

protected:

	void HandleEvents(const SDL_Event& event);
	void HandleWindowEvent(const SDL_WindowEvent& windowEvent);
	void HandleQuitEvent(const SDL_Event& event);
	void HandleMouseMotionEvent(const SDL_MouseMotionEvent& motionEvent);
	void HandleMouseWheelEvent(const SDL_MouseWheelEvent& wheelEvent);
	void HandleMouseButtonDownEvent(const SDL_MouseButtonEvent& mouseEvent);
	void HandleMouseButtonUpEvent(const SDL_MouseButtonEvent& mouseEvent);
	void HandleDropEvent(const SDL_DropEvent& dropEvent);

	void DrawDrawable();

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SelectionArea* selectionArea = nullptr;
	Image* droppedImage = nullptr;

	int logicalHeightBase = 2000;

	float zoom = 1.f;
	float zoomStep = 0.1f;
	float maxZoom = 10.f;
	float minZoom = 0.5f;

	Vector<int> graphOffset;
	Vector<int> graphDrag;

	bool running = false;
	bool isDragging = false;

private:

	Vector<float> GetGlobalToLogicalPosition() const;

};

#endif // !LAZYWINDOW_H