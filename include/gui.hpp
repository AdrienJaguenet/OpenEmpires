#ifndef GUI_HPP_
#define GUI_HPP_

#include <vector>
#include <SDL/SDL.h>

class GuiElement
{
    protected:
        SDL_Rect pos;
        SDL_Surface* surface;
        std::vector<GuiElement*> children;
        GuiElement* parent;
    public:
        GuiElement(int height, int width, GuiElement* parent = NULL);
       ~GuiElement();

        inline int getWidth(){return surface->w;}
        inline int getHeight(){return surface->h;}
        inline int getPosX(){return pos.x;}
        inline int getPosY(){return pos.y;}
        inline SDL_Surface* getSurface(){return surface;}
        inline void setPosX(int x){pos.x = x;}
        inline void setPosY(int y){pos.y = y;}
        inline void setPos(int x, int y){pos.x = x; pos.y = y;}
        inline void moveX(int x){pos.x += x;}
        inline void moveY(int y){pos.y += y;}
        inline void move(int x, int y){pos.x += x; pos.y += y;}
        
        void setWidth(int width);
        void setHeight(int height);
        void resize(int width, int height);
        void draw(SDL_Surface* screen = NULL, int offx = 0, int offy = 0);

};

#endif

