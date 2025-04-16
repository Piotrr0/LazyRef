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
	Vector<int> GetGraphOffset() const { return graphOffset; }

protected:

	void Tick();
	Node* IsMouseOverNode() const;

	void HandleEvents(const SDL_Event& event);
	void HandleWindowEvent(const SDL_WindowEvent& windowEvent);
	void HandleQuitEvent(const SDL_Event& event);
	void HandleMouseMotionEvent(const SDL_MouseMotionEvent& motionEvent);
	void HandleMouseWheelEvent(const SDL_MouseWheelEvent& wheelEvent);
	void HandleMouseButtonDownEvent(const SDL_MouseButtonEvent& mouseEvent);
	void HandleMouseButtonUpEvent(const SDL_MouseButtonEvent& mouseEvent);
	void HandleDropEvent(const SDL_DropEvent& dropEvent);

	void DrawDrawable() const;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SelectionArea* selectionArea = nullptr;
	NodeController* nodeController = nullptr;

	int logicalHeightBase = 2000;

	Vector<int> graphOffset;

	bool running = false;
	bool isDragging = false;
	bool moveSelected = false;
};

#endif // !LAZYWINDOW_H