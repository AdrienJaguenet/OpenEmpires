#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <vector>
#include <string>
#include "entities.hpp"

class Player
{
    private:
        std::string name;
        std::vector<Entity*> owned_entities;
        int id;

    public:
        Player(std::string name, int id);

        inline std::string & getName(){return name;}
        inline void setName(std::string n){name = n;}
        inline std::vector<Entity*> & getOwnedEntities(){return owned_entities;}
        inline int getId(){return id;}
        inline void setId(int nid){id = nid;}

};

#endif

