#include "../include/technology.hpp"
#include <iostream>

Technology::Technology(std::string name) :
name(name),
state(0x0)
{
}

void Technology::startResearch()
{
    elapsedResearchTime = 0;
    state |= TECH_RESEARCHING;
}

void Technology::updateState(int ms)
{
    if(not (state & TECH_AVAILABLE))
    {
        bool tech_available = true;
        for(int i(0); i < requirement.size(); ++i)
        {
            if(not requirement[i]->isResearched())
            {
                tech_available = false;
                break;
            }
        }
        if(tech_available)
        {
            state |= TECH_AVAILABLE;
        }
    }
    if(state & TECH_RESEARCHING)
    {
        elapsedResearchTime += ms;
        if(elapsedResearchTime >= researchTime)
        {
            state &= ~TECH_RESEARCHING;
            state |= TECH_RESEARCHED;
            researchAction();
        }
    }
}

void Technology::researchAction()
{
    std::cout << "Hello, I am the standard technology research message\n";
}

void Technology::setRequirement(Technology* tech)
{
    for(int i(0); i < requirement.size(); ++i)
    {
        if(requirement[i] == tech)
            return;
    }
    requirement.push_back(tech);
}

bool Technology::hasRequirement(Technology* tech)
{
    for(int i(0); i < requirement.size(); ++i)
    {
        if(requirement[i] == tech)
        {
            return true;
        }
    }
    return false;
}

void Technology::removeRequirement(Technology* tech)
{
    for(int i(0); i < requirement.size(); ++i)
    {
        if(requirement[i] == tech)
        {
            requirement.erase(requirement.begin() + i);
        }
    }
}

void Technology::consoleDescription()
{
    std::cout<<"This is a basic technology description"<<std::endl;
}

