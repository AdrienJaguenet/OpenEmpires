#include "entities.hpp"

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

