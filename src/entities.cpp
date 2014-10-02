#include "../include/entities.hpp"
#include "../include/render.hpp"
#include "../include/util.hpp"

#include <SDL/SDL_image.h>
#include <iostream>

ProtoEntity::ProtoEntity(std::string path, std::string id,
        int nframes, int framerate)
{
    image = IMG_Load(path.c_str());
    if(image == NULL)
    {
        std::cout<<"Error: couldn't load \""<<path<<"\"."<<std::endl;
    }
    monochromizeImage(image, SDL_MapRGB(image->format, 255, 0, 0));
}

ProtoEntity::~ProtoEntity()
{
    if(image != NULL)
    {
        SDL_FreeSurface(image);
    }
}

Entity::Entity(ProtoEntity * proto) : proto(proto), posx(0.), posy(0.)
{
}

bool cmpEntPos(Entity* a, Entity* b)
{
    double ia = -a->posy + a->posx;
    double ib = -b->posy + b->posx;
    return ia > ib;
}

