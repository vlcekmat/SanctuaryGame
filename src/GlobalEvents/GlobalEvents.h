#include <iostream>
#include "../Effect/Effect.h"
#include "../../libs/json.hpp"

#pragma once

using json = nlohmann::json;
using namespace std;

/** @brief Events randomly called from EventHandler*/
class GlobalEvent{
public:
    GlobalEvent();

    /** Name of the event*/
    string name;
    /** Effect of the event*/
    pair<string, int> effect;
    /** How likely it is that this event gets picked by the EventHandler*/
    int probability;


    virtual ~GlobalEvent();
};

/** @brief Class that stores instances of GlobalEvent*/
class EventPool{
public:
    /** Calls loadEventsFile(string)*/
    EventPool();

    /** Vector that actually holds pointers to initialized events*/
    vector<GlobalEvent *> event_vector;

    /** Frees allocated memory*/
    ~EventPool();

};