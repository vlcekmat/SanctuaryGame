#include <iostream>
#include <list>
#include <memory>
#include "./Settlement.h"

#pragma once

using namespace std;
using SettlementPtr = shared_ptr<Settlement>;

/** @brief Class containing state of the AI player*/
class AIState{
public:
    AIState();
    /** List of all populated raider settlements*/
    list<SettlementPtr> settlements;
    /** Global raider population*/
    size_t population;
    /** Simplified version of resources, AI uses only this and population as a currency*/
    size_t resources;
    virtual ~AIState();
};
