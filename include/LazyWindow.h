#ifndef LAZYWINDOW_H
#define LAZYWINDOW_H

#include <SDL2/SDL.h>
#include "Vector.h"

class SelectionArea;
class Image;
class Node;
class NodeController;
struct SDL_Renderer;
struct SDL_Window;

class LazyWindow
{
public:
	LazyWindow(const int width, const int height);
	~LazyWindow();
	void StartRendering();

	SDL_Renderer* GetRenderer() const { return renderer; }
	Vector<int> MouseToCanvas() const;
	Vector<int> MouseGlobalToCanvas() const;
	int CalculateLogicalWidth(float width, float height) const;

protected:

	void Tick() const;
	Node* IsMouseOverNode() const;

	void HandleEvents(const SDL_Event& event);
	void HandleWindowEvent(const SDL_WindowEvent& windowEvent) const;
	void HandleQuitEvent(const SDL_Event& event);
	void HandleKeyDown(const SDL_KeyboardEvent& keyboardEvent) const;
	void HandleMouseMotionEvent(const SDL_MouseMotionEvent& motionEvent) const;
	void HandleMouseWheelEvent(const SDL_MouseWheelEvent& wheelEvent);
	void HandleMouseButtonDownEvent(const SDL_MouseButtonEvent& mouseEvent);
	void HandleMouseButtonUpEvent(const SDL_MouseButtonEvent& mouseEvent);
	void HandleDropEvent(const SDL_DropEvent& dropEvent) const;

	void DrawDrawable() const;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SelectionArea* selectionArea = nullptr;
	NodeController* nodeController = nullptr;

	bool running = false;
	bool isDragging = false;
	bool moveSelected = false;
};

#endif // !LAZYWINDOW_H