#include "../include/util.hpp"

Uint32 SDL_GetPixel(SDL_Surface* surface, int x, int y)
{
    Uint32* pixels = (Uint32*) surface->pixels;
    if(x >= 0 && x < surface->w && y >= 0 && y < surface->h)
    {
        return pixels[x + y * surface->w];
    }
}

void SDL_GetPixel(SDL_Surface* surface, int x, int y, Uint32 pixel)
{
    Uint32* pixels = (Uint32*) surface->pixels;
    if(x >= 0 && y < surface->w && y >= 0 && y < surface->h)
    {
        pixels[x + y * surface->w] = pixel;
    }
}

void monochromizeImage(SDL_Surface* surface, Uint32 color)
{
    SDL_LockSurface(surface);
    Uint32 alphaMask = surface->format->Amask;
    Uint32* pixels = (Uint32*) surface->pixels;
    for(int i(0); i < surface->w; ++i)
    {
        for(int j(0); j < surface->h; ++j)
        {
            if(pixels[i + j * surface->w] & alphaMask)
            {
                pixels[i + j * surface->w] = color;
            }
        }
    }
    SDL_UnlockSurface(surface);
}

