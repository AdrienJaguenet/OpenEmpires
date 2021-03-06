#ifndef GUI_HPP_
#define GUI_HPP_

#include <vector>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "map.hpp"
#include "render.hpp"

extern TTF_Font* FONT_SANS_STD_12;

extern SDL_Color COLOR_BLACK;
extern SDL_Color COLOR_WHITE;

void loadFonts();

void unloadFonts();

typedef class GuiElement GuiElement;

typedef void (*EventFunc)(GuiElement*, SDL_MouseButtonEvent*, void*);

class GuiElement
{
    protected:
        SDL_Rect pos;
        SDL_Surface* surface;
        std::vector<GuiElement*> children;
        GuiElement* parent;
        Uint8 color[4];
        GuiElement();//void constructor for inherited classes
        void* onClickData;
        void* onReleaseData;
        EventFunc onClick;
        EventFunc onRelease;
    public:
        GuiElement(int width, int height, GuiElement* parent = NULL);
       ~GuiElement();

        inline int getWidth(){return surface->w;}
        inline int getHeight(){return surface->h;}
        inline int getPosX(){return pos.x;}
        inline int getPosY(){return pos.y;}
        inline SDL_Surface* getSurface(){return surface;}
        inline char getColorR(){return color[0];}
        inline char getColorG(){return color[1];}
        inline char getColorB(){return color[2];}
        inline char getColorA(){return color[3];}
        inline void setPosX(int x){pos.x = x;}
        inline void setPosY(int y){pos.y = y;}
        inline void setPos(int x, int y){pos.x = x; pos.y = y;}
        inline void moveX(int x){pos.x += x;}
        inline void moveY(int y){pos.y += y;}
        inline void move(int x, int y){pos.x += x; pos.y += y;}
        inline void attachElement(GuiElement* e){children.push_back(e);
            rearrange();}
        inline void setColor(char r, char g, char b, char a = 255)
        {color[0] = r; color[1] = g; color[2] = b; color[3] = a;}

        /*although the following lines may appear obscure, they are pretty 
        simple: setters and getters of function pointers*/

        inline void setOnClick(EventFunc oC){onClick = oC;}
        inline void setOnRelease(EventFunc oR){onRelease = oR;}
        inline EventFunc getOnCLick(){return onClick;}
        inline EventFunc getOnRelease(){return onRelease;}
        // end of esoteric code

        //moar event-related inlined functions
        inline void* getOnClickData(){return onClickData;}
        inline void setOnClickData(void *data){onClickData = data;}
        inline void* getOnReleaseData(){return onReleaseData;}
        inline void setOnReleaseData(void *data){onReleaseData = data;}

        inline bool pointInside(int rx, int ry)
        {return rx >= pos.x && rx < pos.x + surface->w
             && ry >= pos.y && ry < pos.y + surface->h;}

        void rearrange();
        virtual void redraw();
        void setWidth(int width);
        void setHeight(int height);
        void resize(int width, int height);
        void draw(SDL_Surface* screen = NULL,
            int offx = 0, int offy = 0);
        virtual void click(SDL_MouseButtonEvent* event);
        virtual void release(SDL_MouseButtonEvent* event);
};

class GuiLabel : public virtual GuiElement
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
        void redraw();
};

class GuiButton : public virtual GuiElement
{
    protected:
        SDL_Surface* pressed_surface;
        GuiButton(GuiElement* parent);
        bool pressed;
    public:
       ~GuiButton();
        void click(SDL_MouseButtonEvent* e);
        void release(SDL_MouseButtonEvent* e);
};

class GuiLabelButton : public GuiLabel, public GuiButton
{
    public:
        GuiLabelButton(std::string text, GuiElement* parent, TTF_Font* font);
       ~GuiLabelButton();
        void redraw();
};

class GuiProgressBar : public GuiElement
{
    protected:
        double fillAmount;//between 1 and 0
        char fillColor[4];
    public:
        GuiProgressBar(int width, int height, GuiElement* parent);
        virtual void redraw();
        inline void setFillColorR(char r){fillColor[0] = r;}
        inline void setFillColorG(char g){fillColor[1] = g;}
        inline void setFillColorB(char b){fillColor[2] = b;}
        inline void setFillColorA(char a){fillColor[3] = a;}
        inline void setFillColor(char r, char g, char b, char a=255)
        {fillColor[0] = r; fillColor[1] = g; fillColor[2] = b;
            fillColor[3] = a;}

        inline char getFillColorR(){return fillColor[0];}
        inline char getFillColorG(){return fillColor[1];}
        inline char getFillColorB(){return fillColor[2];}
        inline char getFillColorA(){return fillColor[3];}

        inline void setFillAmount(double fa){fillAmount = fa;}
        inline double getFillAmount(){return fillAmount;}

        void debugColors();
};

class GuiMap : public GuiElement
{
    protected:
        Map* map;
        Player* player;
        int camx, camy;
        int camsx, camsy;
    public:
        GuiMap(int width, int height, GuiElement* parent, Map*m, Player* p);

        inline Map* getMap(){return map;}
        inline Player* getPlayer(){return player;}
        inline void setMap(Map* m){map = m;}
        inline void setPlayer(Player* p){player = p;}

        inline int getCamX(){return camx;}
        inline int getCamY(){return camy;}
        inline int getCamSX(){return camsx;}
        inline int getCamSY(){return camsy;}
        inline void setCamX(int x){camx = x;}
        inline void setCamY(int y){camy = y;}
        inline void setCam(int x, int y){camx = x; camy = y;}
        inline void setCamSX(int x){camsx = x;}
        inline void setCamSY(int y){camsy = y;}
        inline void setCamS(int x, int y){camsx = x; camsy = y;}
        inline void moveCamX(int x){camx += x;}
        inline void moveCamY(int y){camy += y;}
        inline void moveCam(int x, int y){camx += x; camy += y;}

        inline void update(int ms){camx += camsx; camy += camsy;}

        void redraw();

        void click(SDL_MouseButtonEvent* e);
        void release(SDL_MouseButtonEvent* e);
};

#endif

