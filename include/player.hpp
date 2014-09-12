#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <vector>
#include <string>
#include "entities.hpp"

class Player
{
    private:
        std::string name;
        std::vector<Entity*> entity;
        std::vector<ProtoEntity*> proto_entity;

    public:
        Player(std::string name);
       ~Player();
        inline std::string & getName(){return name;}
        inline void setName(std::string n){name = n;}
        inline std::vector<Entity*> & getEntities(){return entity;}
        inline std::vector<ProtoEntity*> & getProtoEntities()
            {return proto_entity;}
};

#endif

