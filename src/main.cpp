#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "../include/map.hpp"
#include "../include/render.hpp"
#include "../include/entities.hpp"
#include "../include/gui.hpp"
#include <iostream>
#include <math.h>

void placeRandomBush(GuiElement* elm, SDL_MouseButtonEvent* event, void* data)
{
    double x, y;
    Map* map = (Map*) data;
    x = (double)(rand() % 1000) / 1000. * (double)map->getWidth();
    y = (double)(rand() % 1000) / 1000. * (double)map->getHeight();
    map->spawn_entity(0, "bush", x, y);
}

void placeRandomPeasant(GuiElement* elm, SDL_MouseButtonEvent* event,
        void* data)
{
    double x, y;
    Map* map = (Map*) data;
    x = (double)(rand() % 1000) / 1000. * (double)map->getWidth();
    y = (double)(rand() % 1000) / 1000. * (double)map->getHeight();
    map->spawn_entity(0, "peasant", x, y);
}

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
    TTF_Init();
    SDL_Surface* screen = SDL_SetVideoMode(screen_width, screen_height,
        32, window_flags);
    Map map(50, 50);
    map.addPlayer(new Player("Gaia"));
    loadTiles();
    loadFonts();
    //test
    SDL_Event e;
    double x, y;
    int keep_going = 1;
    GuiElement mainGui(screen->w, screen->h / 2);
    mainGui.setPosY(screen->h / 2);
    GuiLabelButton bush("Bush", &mainGui, FONT_SANS_STD_12);
    mainGui.setColor(125, 125, 125, 255);
    bush.setOnClick(placeRandomBush);
    bush.setOnClickData(&map);
    GuiLabelButton peasant("Peasant", &mainGui, FONT_SANS_STD_12);
    peasant.setOnClick(placeRandomPeasant);
    peasant.setOnClickData(&map);
    do
    {
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    screenToMap(e.button.x, e.button.y, camx, camy, x, y);
                    map.setTile(1, floor(x), floor(y));
                    mainGui.click(&(e.button));
                    break;

                case SDL_MOUSEBUTTONUP:
                    mainGui.release(&(e.button));
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
                        mainGui.setWidth(screen->w);
                        mainGui.setPosY(screen->h - mainGui.getHeight());
                        break;
            }
        }
        camx += camsx;
        camy += camsy;
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        renderMap(screen, map, camx, camy);
        mainGui.draw(screen);
        SDL_Flip(screen);
    } while(keep_going);
    //---------
    unloadTiles();
    unloadFonts();
    SDL_FreeSurface(screen);
    SDL_Quit();
    TTF_Quit();
    return 0;
}

