#include <iostream>
#include <random>
#include <memory>
#include "../EffectHandler/EffectHandler.h"
#include "../GlobalEvents/GlobalEvents.h"
#include "../WinConditions/WinConditions.h"
#include "../Combat/Combat.h"

#pragma once

/** @brief Class that catches and executes world events*/
class EventHandler{
public:
    /** Constructor loads possible world events from a json file and inserts them into a memory pool*/
    EventHandler(GameState & game_state, shared_ptr<AI> & _ai);

    /** Method that picks a random event based on their probability, executes it's effect and prints information to the console*/
    void callRandomEvent();

    /** Defines actions that get executed every turn (for example food consumption)*/
    bool doEveryTurn();

    /** Deletes all allocated events*/
    virtual ~EventHandler();
    EventPool event_pool;

    GameState & g_state;
    EffectHandler * eff_han;

    unique_ptr<WinConditionsHandler> winConditionsHandler;

    shared_ptr<AI> & ai;
};