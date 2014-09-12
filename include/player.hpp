#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <vector>
#include <string>
#include "entities.hpp"
#include "technology.hpp"

class Player
{
    private:
        std::string name;
        std::vector<Entity*> entity;
        std::vector<ProtoEntity*> proto_entity;
        std::vector<Technology*> tech_tree;

    public:
        Player(std::string name);
       ~Player();
        inline std::string & getName(){return name;}
        inline void setName(std::string n){name = n;}
        inline std::vector<Entity*> & getEntities(){return entity;}
        inline std::vector<ProtoEntity*> & getProtoEntities()
            {return proto_entity;}
        inline std::vector<Technology*> & getTechTree()
            {return tech_tree;}
};

#endif

