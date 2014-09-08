#include "map.hpp"

Map::Map(int width, int height) : width(width), height(height)
{
    tile = new short**[width];
    for(int i(0); i < width; ++i)
    {
        tile[i] = new short*[height];
        for(int j(0); j < height; ++j)
        {
            tile[i][j] = new short[N_DATA_LAYERS];
            for(int k(0); k < N_DATA_LAYERS; ++k)
            {
                tile[i][j][k] = 0;
            }
        }
    }
}

Map::~Map()
{
    for(int i(0); i < width; ++i)
    {
        for(int j(0); j < height; ++j)
        {
            delete tile[i][j];
        }
        delete tile[i];
    }
    delete tile;
    for(int i(0); i < entities.size(); ++i)
    {
        delete entities[i];
    }
}

void Map::setTile(short value, int x, int y, int layer)
{
    if(x >= 0 && y >= 0 && x < width && y < height)
    {
        tile[x][y][layer] = value;
    }
}

