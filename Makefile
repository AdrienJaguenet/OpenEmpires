FILES=main.cpp render.cpp map.cpp entities.cpp
LIBS=-lSDL -lSDL_image -lm
OPTIONS = --std=c++11

all:
	g++ -o oe $(FILES) $(LIBS) $(OPTIONS)
debug:
	g++ -o oe_debug $(FILES) $(LIBS) $(OPTIONS)
