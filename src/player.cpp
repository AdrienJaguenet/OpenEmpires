#include "../include/player.hpp"

Player::Player(std::string name) : name(name)
{
    //create proto entities
    proto_entity.push_back(new ProtoEntity("data/graphic/bush.png"));
}

Player::~Player()
{
    for(int i(0); i < proto_entity.size(); ++i)
    {
        delete proto_entity[i];
    }
}

