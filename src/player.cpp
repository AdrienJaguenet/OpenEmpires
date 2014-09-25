#include "../include/player.hpp"
#include <iostream>

Player::Player(std::string name) : name(name)
{
    //create proto entities
    proto_entity["bush"] = new ProtoEntity("data/graphic/bush.png",
            "bush");
    proto_entity["peasant"] = new ProtoEntity("data/graphic/peasant.png",
            "peasant");
}

Player::~Player()
{
    for(auto &ent : proto_entity)
    {
        delete ent.second;
    }
    for(auto &tech : tech_tree)
    {
        delete tech.second;
    }
    for(auto &ent : entity)
    {
        delete ent;
    }
}

void Player::spawn_entity(std::string proto, double posx, double posy)
{
    if(proto_entity.find(proto) == proto_entity.end())
    {
        std::cout<<"WARNING: attempted to spawn an entity with non valid";
        std::cout<<" id \""<<proto<<"\""<<std::endl;
        return;
    }
    Entity* ent = new Entity(proto_entity[proto]);
    ent->setPos(posx, posy);
    entity.push_back(ent);
}


