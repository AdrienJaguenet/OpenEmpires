#ifndef ENTITIES_HPP_
#define ENTITIES_HPP_

#include <string>
#include <SDL/SDL.h>

class ProtoEntity
{
    private:
        double ground_width;
        double ground_height;
        SDL_Surface* image;
        int nframes;
        int framerate;
    //other misc
    public:
        ProtoEntity(std::string img_path, int nframes = 1, int framerate = 1);
       ~ProtoEntity();
        inline void setGroundWidth(double nw){ground_width = nw;}
        inline void setGroundHeight(double nh){ground_height = nh;}
        inline double getGroundHeight(){return ground_height;}
        inline double getGroundWidth(){return ground_width;}
};

class Entity
{
    private:
        double posx;
        double posy;
        ProtoEntity & proto;
    public:
        Entity(ProtoEntity & proto);
        inline double getPosX(){return posx;}
        inline double getPosY(){return posy;}
};

std::vector<ProtoEntities> proto_entities;

void loadProtoEntities();

void unloadProtoEntities();

#endif

