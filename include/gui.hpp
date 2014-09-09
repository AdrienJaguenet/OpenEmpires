#ifndef GUI_HPP_
#define GUI_HPP_

#include <vector>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

extern TTF_Font* FONT_SANS_STD_12;

extern SDL_Color COLOR_BLACK;
extern SDL_Color COLOR_WHITE;

void loadFonts();

void unloadFonts();

class GuiElement
{
    protected:
        SDL_Rect pos;
        SDL_Surface* surface;
        std::vector<GuiElement*> children;
        GuiElement* parent;
        GuiElement();//void constructor for inherited classes
    public:
        GuiElement(int width, int height, GuiElement* parent = NULL);
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
        inline void attachElement(GuiElement* e){children.push_back(e);}
        
        void setWidth(int width);
        void setHeight(int height);
        void resize(int width, int height);
        void draw(SDL_Surface* screen = NULL,
            int offx = 0, int offy = 0);
};

class GuiLabel : public GuiElement
{
    protected:
        std::string text;
        TTF_Font* font;
    public:
        GuiLabel(std::string text, GuiElement* parent, TTF_Font* font);

        inline std::string & getText(){return text;}
        inline TTF_Font* getFont(){return font;}
        void setFont(TTF_Font* new_font);
        void setText(std::string new_text);
};

#endif

