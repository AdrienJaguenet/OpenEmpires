#ifndef RENDER_HPP_
#define RENDER_HPP_

#include <SDL/SDL.h>
#include <string>
#include "map.hpp"

#define N_TILES 1

int loadTile(std::string path, int nframes, int framerate);

void loadTiles();

void unloadTiles();

void renderMap(SDL_Surface* screen, Map & map, int offx, int offy);

void screenToMap(int sx, int sy, int offx, int offy,  double & mx, double & my);

#endif

