#ifndef SELECTIONAREA_H
#define SELECTIONAREA_H

#include "Vector.h"
#include "components/Rect.h"
#include "Drawable.h"

struct SDL_Renderer;

class SelectionArea : public Drawable
{
public:
	SelectionArea(SDL_Renderer* renderer);
	~SelectionArea() {}

	void StartSelecting(const Vector<int>& anchor);
	void StopSelecting();

	virtual void Draw(SDL_Renderer* renderer) const override;

	Vector<int> anchorPoint;
	Vector<int> endPoint;

	bool selectionAreaActive = false;

protected:

	SDL_Renderer* renderer = nullptr;

	SDL_Color selectionColor = { 0, 128, 255, 100 };
	mutable Rect areaRect;

};

#endif // !SELECTIONAREA_H
