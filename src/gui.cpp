#include "../include/gui.hpp"

#include <iostream>

#define LOAD_FONT(font, size, path) font = TTF_OpenFont(path, size);\
if(font == NULL) \
{\
    std::cout<<"FATAL: failed to open font \""<<path<<"\""<<std::endl;\
    std::cout<<"\tReason: "<<TTF_GetError()<<std::endl;\
}

TTF_Font* FONT_SANS_STD_12;
SDL_Color COLOR_BLACK = (SDL_Color){0, 0, 0, 255};
SDL_Color COLOR_WHITE = (SDL_Color){255, 255, 255, 255};

void loadFonts()
{
    LOAD_FONT(FONT_SANS_STD_12, 12, "data/fonts/FreeSans.ttf")
}

void unloadFonts()
{
    TTF_CloseFont(FONT_SANS_STD_12);
}

GuiElement::GuiElement(int width, int height, GuiElement* parent) :
parent(parent)
{
    pos.x = 0;
    pos.y = 0;
    if(parent != NULL)
    {
        parent->attachElement(this);
        if(height == -1)
        {
            height = parent->getHeight();
        }
        if(width == -1)
        {
            width = parent->getWidth();
        }
    }
    surface = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32,
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
    if(screen == NULL)
    {
        if(parent == NULL)
        {
            std::cout<<"WARNING: attempted to draw GuiElement with no ";
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
        children[i]->draw(screen);
    }
}

GuiElement::GuiElement()//yes, void constructor
{
}

GuiLabel::GuiLabel(std::string text, GuiElement* parent, TTF_Font* font) : 
GuiElement(),
font(font)
{
    surface = NULL;
    parent = parent;
    if(parent != NULL)
    {
        parent->attachElement(this);
    }
    pos.x = 0;
    pos.y = 0;
    setText(text);
}

void GuiLabel::setText(std::string new_text)
{
    text = new_text;
    if(surface != NULL)
    {
        SDL_FreeSurface(surface);
    }
    surface = TTF_RenderText_Blended(font, text.c_str(), COLOR_WHITE);
    if(surface == NULL)
    {
        std::cout<<"FATAL: Couldn't render text"<<std::endl;
        std::cout<<"\tReason: "<<TTF_GetError()<<std::endl;
    }
}

void GuiLabel::setFont(TTF_Font* new_font)
{
    font = new_font;
    setText(text);
}

