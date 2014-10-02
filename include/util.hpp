#ifndef UTIL_HPP_INCLUDED
#define UTIL_HPP_INCLUDED

#include <SDL/SDL.h>

Uint32 SDL_GetPixel(SDL_Surface* surface, int x, int y);

void SDL_SetPixel(SDL_Surface* surface, int x, int y, Uint32 pixel);

void monochromizeImage(SDL_Surface* surface, Uint32 pixel);

#endif

