#include "Image.h"
#include "Node.h"
#include <stb_image/stb_image.h>
#include "SDL2/SDL.h"
#include "LazyWindow.h"
#include "Vector.h"

Image::Image(LazyWindow* window, const Vector<int>& position, const char* imageFile) :
    Node(window, position)
{
    texture = loadTextureFromFile(imageFile, window->GetRenderer());
    if (texture)
    {
        int w, h;
        SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
        nodeRect.SetRect(position, position + Vector<int>(w, h));
    }
}

Image::~Image()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
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

void Image::Draw() const
{
    if (texture)
    {
        SDL_Rect destRect = 
        {
            position.x + window->GetGraphOffset().x,
            position.y + window->GetGraphOffset().y,
            static_cast<int>(nodeRect.GetWidth() * window->GetZoom()),
            static_cast<int>(nodeRect.GetHeight() * window->GetZoom())
        };

        SDL_RenderCopy(window->GetRenderer(), texture, nullptr, &destRect);
    }
}