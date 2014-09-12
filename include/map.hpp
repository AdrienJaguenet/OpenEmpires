#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include "entities.hpp"
#include "player.hpp"

#define N_DATA_LAYERS 1

#define DATALAYER_TERRAIN 0

class Map
{
    private:
        //[x][y][data layer]
        short*** tile;
        int width;
        int height;
        std::vector<Player*> player;
    public:
        Map(int width, int height);
       ~Map();
        inline int getWidth(){return width;}
        inline int getHeight(){return height;}
        inline short getTile(int x, int y, int layer){return tile[x][y][layer];}
        void setTile(short value, int x, int y, int layer = 0);
        inline std::vector<Player*> & getPlayers(){return player;}
        inline void addPlayer(Player* p){player.push_back(p);}
};

#endif

