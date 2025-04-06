#ifndef IMAGE_H
#define IMAGE_H

#include "Node.h"
#include "Vector.h"

class SDL_Texture;

class Image : public Node
{
public:
	Image(SDL_Renderer* renderer, const Vector<int>& position, const char* imageFile);
	static SDL_Texture* loadTextureFromFile(const char* imageFile, SDL_Renderer* renderer);

	virtual void Draw() override;
	SDL_Texture* GetTexture() const { return texture;}

protected:
	SDL_Texture* texture;

};

#endif // IMAGE_H