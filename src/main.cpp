#include <SDL2/SDL.h>
#undef main

#include <iostream>
#include "LazyWindow.h"

int main(int argc, char* argv[]) 
{
    SDL_Init(SDL_INIT_VIDEO);

    LazyWindow lazyWindow(800, 600);
    lazyWindow.StartRendering();
    
    SDL_Quit();

    return 0;
}