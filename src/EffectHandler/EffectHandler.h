#include <iostream>
#include <map>
#include "../Effect/Effect.h"

#pragma once

using namespace std;

/** @brief Class that stores information about all possible effects and calls them when needed*/
class EffectHandler{
public:
    /** Constructor initializes all known effects (similarly to commands)*/
    EffectHandler( GameState & game_state );

    /** Finds the given effect in the effectPool and calls it with the specified value*/
    void callEffect(string name, int value, int multiplier);

    /** Destructor frees all allocated memory*/
    ~EffectHandler();

    /** Map of all known effects that can be used in buildings and/or global events*/
    map<string, Effect*> effectPool;

    /** Reference to the current instance of GameState - used to modify game variables*/
    GameState & g_state;
};