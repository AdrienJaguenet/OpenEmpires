FILES=main.cpp render.cpp map.cpp entities.cpp player.cpp gui.cpp technology.cpp
LIBS=-lSDL -lSDL_image -lSDL_ttf -lm
OPTIONS = --std=c++11 -g

all:
	cd src/; \
	g++ -o ../oe $(FILES) $(LIBS) $(OPTIONS)
