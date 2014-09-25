#include "../include/render.hpp"
#include <vector>
#include <SDL/SDL_image.h>
#include <iostream>

std::vector<SDL_Surface*> tile_img;

int TILE_HEIGHT;
int TILE_WIDTH;

double S2M_SLOPE;

int loadTile(std::string path, int nframes, int framerate)
{
    SDL_Surface* img = IMG_Load(path.c_str());
    if(img == NULL)
    {
        std::cout<<"Error at loading \""<<path<<"\""<<std::endl;
        tile_img.push_back(NULL);
        return -1;
    }
    else
    {
        tile_img.push_back(img);
        return 0;
    }
}

void loadTiles()
{
    loadTile("data/graphic/grass.png", 1, 1);
    TILE_HEIGHT = tile_img[0]->h;
    TILE_WIDTH = tile_img[0]->w;
    S2M_SLOPE = (double) tile_img[0]->h / (double)tile_img[0]->w;
    loadTile("data/graphic/water.png", 1, 1);
}

void unloadTiles()
{
    for(int i(0); i < tile_img.size(); ++i)
    {
        if(tile_img[i] != NULL)
        {
            SDL_FreeSurface(tile_img[i]);
        }
    }
}

void renderMap(SDL_Surface* screen, Map & map, int offx, int offy)
{
    for(int i(0); i < map.getWidth(); ++i)
    {
        for(int j(0); j < map.getHeight(); ++j)
        {
            SDL_Rect tmp;
            tmp.x = offx + i * TILE_WIDTH / 2 + j * TILE_WIDTH / 2;
            tmp.y = offy + j * TILE_HEIGHT / 2 - i * TILE_HEIGHT / 2;
            SDL_BlitSurface(tile_img[map.getTile(i, j, DATALAYER_TERRAIN)], 
                NULL, screen, &tmp);
        }
    }
    for(Player* pl : map.getPlayers())
    {
        for(Entity* ent : pl->getEntities())
        {
            ent->draw(screen, offx, offy);
        }
    }
}

void screenToMap(int sx, int sy, int offx, int offy, double & mx, double & my)
{
    mx = ((S2M_SLOPE * (sx - offx) + offy - TILE_HEIGHT / 2) - sy)
    / TILE_HEIGHT + 1;
    my = (sy + S2M_SLOPE * (sx - offx) - offy - TILE_HEIGHT / 2)
    / TILE_HEIGHT;
}

