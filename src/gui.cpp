#include "../include/gui.hpp"

#include <iostream>

GuiElement::GuiElement(int height, int width, GuiElement* parent) :
parent(parent)
{
    pos.x = 0;
    pos.y = 0;
    surface = SDL_CreateRGBSurface(SDL_HWSURFACE, height, width, 32,
        0, 0, 0, 0);
    if(surface == NULL)
    {
        std::cout<<"FATAL: Unable to allocate SDL surface ("<<SDL_GetError();
        std::cout<<" )"<<std::endl;
        std::cout<<"\tAt file "<<__FILE__<<std::endl;
    }
}

GuiElement::~GuiElement()
{
    SDL_FreeSurface(surface);
    for(int i(0); i < children.size(); ++i)
    {
        delete children[i];
    }
}

void GuiElement::setWidth(int width)
{
    resize(width, surface->h);
}

void GuiElement::setHeight(int height)
{
    resize(surface->w, height);
}

void GuiElement::resize(int width, int height)
{
    SDL_FreeSurface(surface);
    surface = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height,
        32, 0, 0, 0, 0);
}

void GuiElement::draw(SDL_Surface* screen, int offx, int offy)
{
    //black fill
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
    if(screen == NULL)
    {
        if(parent == NULL)
        {
            std::cout<<"WARNING: attmpted to draw GuiElement with no ";
            std::cout<<"surface nor parent. Element won't be drawn.\n";
            return;
        }
        SDL_BlitSurface(surface, NULL, parent->getSurface(), &pos);
    }
    else
    {
        SDL_Rect tmp;
        tmp.x = pos.x + offx;
        tmp.y = pos.y + offy;
        SDL_BlitSurface(surface, NULL, screen, &tmp);
    }
    //draw all children
    for(int i(0); i < children.size(); ++i)
    {
        children[i]->draw();
    }
}

