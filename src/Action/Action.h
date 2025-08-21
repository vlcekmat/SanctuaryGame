#include <iostream>
#include <set>
#include <map>
#include <string>
#include <memory>
#include "../../libs/json.hpp"
#include "../EventHandler/EventHandler.h"

#pragma once

using json = nlohmann::json;
using namespace std;

/** @brief Base class for all actions
 *
 *  Actions are custom commands specified by the user in the configuration file
 *
*/
class Action{
public:
    /** names of all effects this action has*/
    set<string> effects;
    /** map that helps translate parameter names*/
    map<string, string> parameterMap;
    /** parameters initialize with a constant in the json file*/
    map<string, int> staticParameters;
    /** what the command looks like*/
    string syntax;
    /** command description showed in the help menu*/
    string description;


    Action(EventHandler & eventHandler);

    virtual void applyEffects(const map<string, int> & parameters);

    virtual ~Action();

    EventHandler & eventHandler;
};

/** @brief Class used to store loaded actions*/
class ActionPool{
public:
    ActionPool();

    set<shared_ptr<Action>> actions;

    virtual ~ActionPool();
};


