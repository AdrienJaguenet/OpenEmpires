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
    if(argc == 3)
    {
        screen_height = atoi(argv[2]);
        screen_width = atoi(argv[1]);
    }
    
    int window_flags = SDL_HWSURFACE |
        SDL_RESIZABLE |
        SDL_DOUBLEBUF;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Surface* screen = SDL_SetVideoMode(screen_width, screen_height,
        32, window_flags);
    Map map(5, 5);
    map.addPlayer(new Player("Gaia"));
    map.spawn_entity(0, "tower", 0, 0);
    loadTiles();
    loadFonts();
    //test
    SDL_Event e;
    double x, y;
    int keep_going = 1;
    GuiElement mainGui(screen->w, screen->h);
    GuiMap guiMap(screen->w, screen->h * 3 / 5, &mainGui, &map, NULL);
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
                    mainGui.click(&(e.button));
                    break;

                case SDL_MOUSEBUTTONUP:
                    mainGui.release(&(e.button));
                    break;

                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_UP:
                            guiMap.setCamSY(10);
                            break;
                        case SDLK_DOWN:
                            guiMap.setCamSY(-10);
                            break;
                        case SDLK_RIGHT:
                            guiMap.setCamSX(-10);
                            break;
                        case SDLK_LEFT:
                            guiMap.setCamSX(10);
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_UP:
                            if(guiMap.getCamSY() > 0) guiMap.setCamSY(0);
                            break;
                        case SDLK_DOWN:
                            if(guiMap.getCamSY() < 0) guiMap.setCamSY(0);
                            break;
                        case SDLK_RIGHT:
                            if(guiMap.getCamSX() < 0) guiMap.setCamSX(0);
                            break;
                        case SDLK_LEFT:
                            if(guiMap.getCamSX() > 0) guiMap.setCamSX(0);
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
                        guiMap.setWidth(screen->w);
                        guiMap.setHeight(screen->h * 4 / 5);
                        mainGui.setHeight(screen->h);
                        break;
            }
        }
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        guiMap.update(0);
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

