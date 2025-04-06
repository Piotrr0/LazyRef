#ifndef IMAGE_H
#define IMAGE_H

#include "Node.h"
#include "Vector.h"
#include <SDL2/SDL.h>

class LazyWindow;

class Image : public Node
{
public:
	Image(LazyWindow* window, const Vector<int>& position, const char* imageFile);
	virtual ~Image();

	static SDL_Texture* loadTextureFromFile(const char* imageFile, SDL_Renderer* renderer);
	virtual void Draw() const override;
	SDL_Texture* GetTexture() const { return texture;}

protected:
	SDL_Texture* texture;
};

#endif // IMAGE_H