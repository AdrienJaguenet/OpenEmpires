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
GuiElement()
{
    this->parent = parent;
    pos.x = 0;
    pos.y = 0;
    surface = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32,
        0, 0, 0, 0);

    if(surface == NULL)
    {
        std::cout<<"FATAL: Unable to allocate SDL surface ("<<SDL_GetError();
        std::cout<<" )"<<std::endl;
        std::cout<<"\tAt file "<<__FILE__<<std::endl;
    }

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
}

GuiElement::~GuiElement()
{
    if(surface != NULL)
    {
        SDL_FreeSurface(surface);
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
    SDL_SetAlpha(surface, SDL_SRCALPHA, color[3]);
    rearrange();
}

void GuiElement::draw(SDL_Surface* screen, int offx, int offy)
{
    redraw();
    //draw all children
    for(GuiElement* child :children)
    {
        child->draw();
    }
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
}

GuiElement::GuiElement()
{
    onClick = NULL;
    onRelease = NULL;
    onClickData = NULL;
    onReleaseData = NULL;
    surface = NULL;
    color[0] = 128;
    color[1] = 128;
    color[2] = 128;
    color[3] = 255;
}

GuiLabel::GuiLabel(std::string text, GuiElement* pparent, TTF_Font* font) : 
GuiElement(),
font(font)
{
    surface = NULL;
    parent = pparent;    
    pos.x = 0;
    pos.y = 0;
    setText(text);
    if(parent != NULL)
    {
        parent->attachElement(this);
    }
}

void GuiLabel::setText(std::string new_text)
{
    text = new_text;
    if(surface != NULL)
    {
        SDL_FreeSurface(surface);
    }
    if(color[3] == 0)
    {
        surface = TTF_RenderText_Blended(font, text.c_str(), COLOR_WHITE);
    }
    else
    {
        SDL_Color bgColor = {color[0], color[1], color[2], color[3]};
        surface = TTF_RenderText_Shaded(font, text.c_str(), COLOR_WHITE, 
                bgColor);
        SDL_SetAlpha(surface, SDL_SRCALPHA, color[3]);
    }
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

void GuiElement::rearrange()
{
    //TODO: take into account margin space
    int currentX(0), currentY(0);
    for(int i(0); i < children.size(); ++i)
    {
        children[i]->setPos(currentX, currentY);
        currentX += children[i]->getWidth();
        if(currentX + children[i]->getWidth() > getWidth())
        {
            currentX = 0;
            currentY += children[i]->getHeight();
        }
    }
}

void GuiElement::redraw()
{
    int h = surface->h, w = surface->w;
    SDL_FreeSurface(surface);
    surface = SDL_CreateRGBSurface(SDL_HWSURFACE,
            w, h, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format,
                color[0], color[1], color[2]));
    SDL_SetAlpha(surface, SDL_SRCALPHA, color[3]);
}

void GuiLabel::redraw()
{
    setText(text);
}

void GuiElement::click(SDL_MouseButtonEvent* event)
{
    if(onClick != NULL && pointInside(event->x, event->y))
    {
        onClick(this, event, onClickData);
    }
    SDL_MouseButtonEvent newevent = *event;
    newevent.x -= pos.x;
    newevent.y -= pos.y;
    for(int i(0); i < children.size(); ++i)
    {
            children[i]->click(&newevent);
    }
}

void GuiElement::release(SDL_MouseButtonEvent* event)
{
    if(onRelease != NULL && pointInside(event->x, event->y))
    {
        onRelease(this, event, onClickData);
    }
    SDL_MouseButtonEvent newevent = *event;
    newevent.x -= pos.x;
    newevent.y -= pos.y;
    for(int i(0); i< children.size(); ++i)
    {
        children[i]->release(&newevent);
    }
}

GuiButton::GuiButton(GuiElement* pparent):
    pressed_surface(NULL),
    pressed(false)
{
}

GuiButton::~GuiButton()
{
    if(pressed_surface != NULL)
    {
        SDL_FreeSurface(pressed_surface);
    }
}

void GuiButton::click(SDL_MouseButtonEvent* e)
{
    if(pointInside(e->x, e->y))
    {
        pressed = true;
    }
    GuiElement::click(e);
}

void GuiButton::release(SDL_MouseButtonEvent* e)
{
    if(pointInside(e->x, e->y))
    {
        pressed = false;
    }
    GuiElement::release(e);
}

GuiLabelButton::GuiLabelButton(std::string text, GuiElement* parent,
        TTF_Font* font) : 
    GuiButton(parent),
    GuiLabel(text, parent, font)
{
}

GuiLabelButton::~GuiLabelButton()
{
    if(pressed_surface != NULL)
    {
        SDL_FreeSurface(pressed_surface);
    }
}

void GuiLabelButton::redraw()
{
    if(not pressed)
    {
        color[0] = 128;
        setText(text);
    }
    else
    {
        color[0] = 255;
        setText(text);
    }
}

GuiProgressBar::GuiProgressBar(int width, int height,
        GuiElement* parent) : 
    GuiElement(width, height, parent),
    fillAmount(0.)
{
    fillColor[0] = 255;
    fillColor[1] = 255;
    fillColor[2] = 255;
    fillColor[3] = 255;
    redraw();
}

void GuiProgressBar::redraw()
{
    int height(surface->h), width(surface->w);
    if(surface != NULL)
    {
        SDL_FreeSurface(surface);
    }
    surface = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32, 
            0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format,
                color[0], color[1], color[2]));
    double fillpx = fillAmount * (double)surface->w;
    SDL_Rect fr;
    fr.x = 0; fr.y = 0; fr.h = surface->h; fr.w = (int)fillpx;
    SDL_FillRect(surface, &fr, SDL_MapRGB(surface->format,
                fillColor[0], fillColor[1], fillColor[2]));
}

void GuiProgressBar::debugColors()
{
    printf("%d\n%d\n%d\n", color[0], color[1], color[2]);
    printf("%d\n%d\n%d\n", fillColor[0], fillColor[1], fillColor[3]);
    printf("=================\n\n");
}

