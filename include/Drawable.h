#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>

struct SDL_Renderer;

class Drawable
{
public:
	Drawable();
	~Drawable();

	virtual void Draw(SDL_Renderer* renderer) const = 0;
	static std::vector<Drawable*> GetAllDrawableObjects();
};

#endif // !DRAWABLE_H
