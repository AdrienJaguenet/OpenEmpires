#include "../include/entities.hpp"
#include "../include/render.hpp"

#include <SDL/SDL_image.h>
#include <iostream>

std::vector<ProtoEntity*> proto_entities;

ProtoEntity::ProtoEntity(std::string path, int nframes, int framerate)
{
    image = IMG_Load(path.c_str());
    if(image == NULL)
    {
        std::cout<<"Error: couldn't load \""<<path<<"\"."<<std::endl;
    }
}

ProtoEntity::~ProtoEntity()
{
    if(image != NULL)
    {
        SDL_FreeSurface(image);
    }
}

void loadProtoEntities()
{
    proto_entities.push_back(new ProtoEntity("bush.png"));
}

void unloadProtoEntities()
{
    for(int i(0); i < proto_entities.size(); ++i)
    {
        delete proto_entities[i];
    }
}

Entity::Entity(ProtoEntity * proto) : proto(proto), posx(0.), posy(0.)
{
}

void Entity::draw(SDL_Surface* screen, int offx, int offy)
{
    SDL_Rect tmp;
    tmp.x = offx + posx * (double)TILE_WIDTH / 2. +
        posy * (double)TILE_WIDTH / 2.;
    tmp.y = offy + posy * (double)TILE_HEIGHT / 2. -
        posx * TILE_HEIGHT / 2.;
    SDL_BlitSurface(proto->getImage(), NULL, screen, &tmp);
}

