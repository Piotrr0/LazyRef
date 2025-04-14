#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>

struct SDL_Renderer;

class Drawable
{
public:
	Drawable();
	virtual ~Drawable();

	virtual void Draw(SDL_Renderer* renderer) const = 0;
	static const std::vector<Drawable*>& GetAllDrawableObjects();

	static void RegisterDrawable(Drawable* drawable);
	static void UnregisterDrawable(Drawable* drawable);
};

#endif // !DRAWABLE_H