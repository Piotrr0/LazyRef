#include "Drawable.h"

namespace
{
	std::vector<Drawable*> drawableObjects;
}

Drawable::Drawable()
{
	RegisterDrawable(this);
}

Drawable::~Drawable()
{
	UnregisterDrawable(this);
}

void Drawable::RegisterDrawable(Drawable* drawable)
{
	if (drawable && std::find(drawableObjects.begin(), drawableObjects.end(), drawable) == drawableObjects.end())
	{
		drawableObjects.push_back(drawable);
	}
}

void Drawable::UnregisterDrawable(Drawable* drawable)
{
	auto it = std::find(drawableObjects.begin(), drawableObjects.end(), drawable);
	if (it != drawableObjects.end())
	{
		drawableObjects.erase(it);
	}
}

const std::vector<Drawable*>& Drawable::GetAllDrawableObjects()
{
	return drawableObjects;
}