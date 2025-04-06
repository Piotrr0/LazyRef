#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>

class Drawable
{
public:
	Drawable();
	~Drawable();

	virtual void Draw() const = 0;
	static std::vector<Drawable*> GetAllDrawableObjects();
};

#endif // !DRAWABLE_H
