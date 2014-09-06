#include <SDL/SDL.h>
#include "map.hpp"
#include "render.hpp"
#include "entities.hpp"
#include <iostream>
#include <math.h>

int main(int argc, char** argv)
{
    int screen_height = 480;
    int screen_width = 640;
    if(argc == 3)
    {
        screen_height = atoi(argv[2]);
        screen_width = atoi(argv[1]);
    }
        
    int camx(0), camy(0);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* screen = SDL_SetVideoMode(screen_width, screen_height,
        32, SDL_HWSURFACE);
    Map map(10, 10);
    loadTiles();
    loadProtoEntities();
    //test
    SDL_Event e;
    double x, y;
    int keep_going = 1;
    do
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                screenToMap(e.button.x, e.button.y, camx, camy, x, y);
                map.setTile(1, floor(x), floor(y));
            }
            else if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_UP:
                        camy += 10;
                        break;
                    case SDLK_DOWN:
                        camy -= 10;
                        break;
                    case SDLK_RIGHT:
                        camx -= 10;
                        break;
                    case SDLK_LEFT:
                        camx += 10;
                        break;
                }
            }
            else if(e.type == SDL_QUIT)
            {
                keep_going = 0;
            }
        }
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        renderMap(screen, map, camx, camy);
        SDL_Flip(screen);
    } while(keep_going);
    //---------
    unloadTiles();
    unloadProtoEntities();
    SDL_FreeSurface(screen);
    SDL_Quit();
    return 0;
}

