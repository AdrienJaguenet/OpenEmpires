#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <vector>
#include <string>
#include <unordered_map>
#include "entities.hpp"
#include "technology.hpp"

using namespace std;

class Player
{
    private:
        string name;
        vector<Entity*> entity;
        unordered_map<string, ProtoEntity*> proto_entity;
        unordered_map<string, Technology*> tech_tree;

    public:
        Player(string name);
       ~Player();
        inline string & getName(){return name;}
        inline void setName(string n){name = n;}
        inline vector<Entity*> & getEntities(){return entity;}
        inline unordered_map<string, ProtoEntity*> & getProtoEntities()
            {return proto_entity;}
        inline unordered_map<string, Technology*> & getTechTree()
            {return tech_tree;}
        void spawn_entity(string proto, double posx, double posy);
};

#endif

