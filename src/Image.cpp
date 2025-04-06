#include "Image.h"
#include "Node.h"
#include <SDL2/SDL.h>
#include <stb_image/stb_image.h>

Image::Image(SDL_Renderer* renderer, const Vector<int>& position, const char* imageFile) :
    Node(renderer, position)
{
    texture = loadTextureFromFile(imageFile, renderer);
}

SDL_Texture* Image::loadTextureFromFile(const char* imageFile, SDL_Renderer* renderer)
{
    int width, height, channels;
    unsigned char* pixels = stbi_load(imageFile, &width, &height, &channels, STBI_rgb_alpha);

    if (!pixels) 
    {
        printf("Failed to load image '%s'. STB Error: %s\n", imageFile, stbi_failure_reason());
        return nullptr;
    }

    const int pitch = width * 4;

    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
        pixels, width, height, 32, pitch,
        0x000000FF,
        0x0000FF00,
        0x00FF0000,
        0xFF000000
    );

    if (!surface)
    {
        printf("Failed to create SDL_Surface for '%s': %s\n", imageFile, SDL_GetError());
        stbi_image_free(pixels);
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) 
    {
        printf("Failed to create SDL_Texture for '%s': %s\n", imageFile, SDL_GetError());
        stbi_image_free(pixels);
        return nullptr;
    }

    stbi_image_free(pixels);
    return texture;
}

void Image::Draw()
{
    if (texture)
    {
        SDL_Rect destRect = { position.x, position.y, 0, 0};
        SDL_QueryTexture(texture, nullptr, nullptr, &destRect.w, &destRect.h);

        SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    }
}
