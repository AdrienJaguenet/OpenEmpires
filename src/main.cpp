#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include "../include/map.hpp"
#include "../include/render.hpp"
#include "../include/entities.hpp"
#include <iostream>
#include <math.h>

int main(int argc, char** argv)
{
    int screen_height = 480;
    int screen_width = 640;
    int camsx = 0, camsy = 0;
    if(argc == 3)
    {
        screen_height = atoi(argv[2]);
        screen_width = atoi(argv[1]);
    }
    
    int window_flags = SDL_HWSURFACE |
        SDL_RESIZABLE |
        SDL_DOUBLEBUF;

    int camx(0), camy(0);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* screen = SDL_SetVideoMode(screen_width, screen_height,
        32, window_flags);
    Map map(10, 10);
    loadTiles();
    loadProtoEntities();
    //test
    SDL_Event e;
    double x, y;
    map.addEntity(new Entity(proto_entities[0]));
    int keep_going = 1;
    do
    {
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    screenToMap(e.button.x, e.button.y, camx, camy, x, y);
                    map.setTile(1, floor(x), floor(y));
                    break;

                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_UP:
                            camsy = 10;
                            break;
                        case SDLK_DOWN:
                            camsy = -10;
                            break;
                        case SDLK_RIGHT:
                            camsx = -10;
                            break;
                        case SDLK_LEFT:
                            camsx = 10;
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_UP:
                            if(camsy == 10) camsy = 0;
                            break;
                        case SDLK_DOWN:
                            if(camsy == -10) camsy = 0;
                            break;
                        case SDLK_RIGHT:
                            if(camsx == -10) camsx = 0;
                            break;
                        case SDLK_LEFT:
                            if(camsx == 10) camsx = 0;
                            break;
                    }
                    break;
                    
                    case SDL_QUIT:
                        keep_going = 0;
                        break;
                    
                    case SDL_VIDEORESIZE:
                        SDL_FreeSurface(screen);
                        screen = SDL_SetVideoMode(e.resize.w, e.resize.h,
                            32, window_flags);
                        break;
            }
        }
        camx += camsx;
        camy += camsy;
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

