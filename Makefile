FILES=main.cpp render.cpp map.cpp entities.cpp player.cpp
LIBS=-lSDL -lSDL_image -lGL -lm
OPTIONS = --std=c++11

all:
	cd src/
	g++ -o oe $(FILES) $(LIBS) $(OPTIONS)
