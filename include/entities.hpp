#ifndef ENTITIES_HPP_
#define ENTITIES_HPP_

#include <string>
#include <SDL/SDL.h>
#include <vector>
#include <algorithm>

class ProtoEntity
{
    private:
        double ground_width;
        double ground_height;
        SDL_Surface* image;
        int nframes;
        int framerate;
        std::string id;
    //other misc
    public:
        ProtoEntity(std::string img_path, std::string id,
                int nframes = 1, int framerate = 1);
       ~ProtoEntity();
        inline void setGroundWidth(double nw){ground_width = nw;}
        inline void setGroundHeight(double nh){ground_height = nh;}
        inline double getGroundHeight(){return ground_height;}
        inline double getGroundWidth(){return ground_width;}
        inline SDL_Surface* getImage(){return image;}
};

class Entity
{
    protected:
        double posx;
        double posy;
        ProtoEntity * proto;
        int playerid;
    public:
        Entity(ProtoEntity * proto);
        inline double getPosX(){return posx;}
        inline double getPosY(){return posy;}
        inline void setPosX(double x){posx = x;}
        inline void setPosY(double y){posy = y;}
        inline void setPos(double x, double y){posx = x, posy = y;}
        inline ProtoEntity* getProto(){return proto;}
        virtual void draw(SDL_Surface* screen, int offx, int offy);

        friend bool cmpEntPos(Entity* a, Entity* b);
};

bool cmpEntPos(Entity* a, Entity* b);

#endif

