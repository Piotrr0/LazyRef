#ifndef IMAGE_H
#define IMAGE_H

#include "Node.h"
#include "Vector.h"

struct SDL_Renderer;

class Image : public Node
{
public:
	Image(const Vector<int>& position, SDL_Texture* image);
	Image(const Vector<int>& position, const Vector<int>& offset, SDL_Texture* image);

	virtual ~Image();
	virtual void Draw(SDL_Renderer* renderer) const override;

	static SDL_Texture* LoadTextureFromFile(const char* imageFile, SDL_Renderer* renderer);

protected:

	SDL_Texture* texture;

};

#endif // IMAGE_H