#include "Drawable.h"

namespace
{
	std::vector<Drawable*> drawableObjects;
}

Drawable::Drawable()
{
	drawableObjects.push_back(this);
}

Drawable::~Drawable()
{
    const auto it = std::find(drawableObjects.begin(), drawableObjects.end(), this);
    if (it != drawableObjects.end())
    {
        drawableObjects.erase(it);
    }
}

std::vector<Drawable*> Drawable::GetAllDrawableObjects()
{
	return drawableObjects;
}
