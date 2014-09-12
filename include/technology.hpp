#ifndef TECHNOLOGY_HPP_
#define TECHNOLOGY_HPP_

#include <vector>
#include <string>

#define TECH_AVAILABLE   0x01
#define TECH_RESEARCHING 0x02
#define TECH_RESEARCHED  0x04
#define TECH_LOCKED      0x08

class Technology
{
    protected:
        //TODO: cost?
        std::vector<Technology*> requirement;
        std::string name;
        char state;
        int researchTime, elapsedResearchTime;
        //TODO: icons and graphic stuff
    public:
        Technology(std::string name);
        inline bool isAvailable(){return TECH_AVAILABLE & state;}
        inline bool isResearching(){return TECH_RESEARCHING & state;}
        inline bool isResearched(){return TECH_RESEARCHED & state;}
        inline bool isLocked(){return TECH_LOCKED & state;}

        inline void setState(char flags){state = flags;}
        inline void lock(){setState(state |= TECH_LOCKED);}
        inline void unlock(){setState(state &= ~TECH_LOCKED);}

        inline void setName(std::string nname){name = nname;}
        inline std::string & getName(){return name;}

        void startResearch();
        virtual void updateState(int ms);
        void setRequirement(Technology* tech);
        bool hasRequirement(Technology* tech);
        void removeRequirement(Technology* tech);

        virtual void researchAction();
        virtual void consoleDescription();
};

#endif

