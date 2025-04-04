/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/* this header is meant to be included after the other related internal SDL
   headers. it's the interface between psp renderer and video driver code. */

#define PSP_SCREEN_WIDTH  480
#define PSP_SCREEN_HEIGHT 272

#define PSP_FRAME_BUFFER_WIDTH 512
#define PSP_FRAME_BUFFER_SIZE  (PSP_FRAME_BUFFER_WIDTH * PSP_SCREEN_HEIGHT)

enum SDL_PSP_RenderProps
{
    SDL_PSP_RENDERPROPS_FRONTBUFFER,
    SDL_PSP_RENDERPROPS_BACKBUFFER,
};

int SDL_PSP_RenderGetProp(SDL_Renderer *r, enum SDL_PSP_RenderProps which, void** out);

