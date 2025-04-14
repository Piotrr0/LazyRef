#include "Image.h"
#include "Node.h"
#include <stb_image/stb_image.h>
#include "SDL2/SDL.h"
#include "Vector.h"

Image::Image(const Vector<int>& position, SDL_Texture* image)
	: Node(position), texture(image)
{
	InitializeFromTexture();
}

Image::Image(const Vector<int>& position, const Vector<int>& offset, SDL_Texture* image)
	: Node(position, offset), texture(image)
{
	InitializeFromTexture();
}

Image::~Image()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

SDL_Texture* Image::LoadTextureFromFile(const char* imageFile, SDL_Renderer* renderer)
{
	if (!imageFile || !renderer) return nullptr;

	int width, height, channels;
	unsigned char* pixels = stbi_load(imageFile, &width, &height, &channels, STBI_rgb_alpha);

	if (!pixels)
	{
		printf("Failed to load image '%s'. STB Error: %s\n", imageFile, stbi_failure_reason());
		return nullptr;
	}

	auto cleanupPixels = [pixels]() { stbi_image_free(pixels); };

	const int pitch = width * 4;
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
		pixels, width, height, 32, pitch,
		0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000
	);

	if (!surface)
	{
		printf("Failed to create SDL_Surface for '%s': %s\n", imageFile, SDL_GetError());
		cleanupPixels();
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!texture)
	{
		printf("Failed to create SDL_Texture for '%s': %s\n", imageFile, SDL_GetError());
		cleanupPixels();
		return nullptr;
	}

	cleanupPixels();
	return texture;
}

void Image::InitializeFromTexture()
{
	if (texture)
	{
		int w, h;
		SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

		baseWidth = w;
		baseHeight = h;
		UpdateTransform(Vector<int>(baseWidth, baseHeight), dropPosition);
	}
}

void Image::Draw(SDL_Renderer* renderer) const
{
	if (!renderer || !texture) return;

	const SDL_Rect rect = nodeRect.ConvertSDLRect();
	SDL_Rect outlineRect = rect;
	outlineRect.x -= 5;
	outlineRect.y -= 5;
	outlineRect.w += 10;
	outlineRect.h += 10;


	if (isSelected)
	{
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
		SDL_RenderFillRect(renderer, &outlineRect);
	}

	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}