#include <iostream>

#pragma once

using namespace std;

/** @brief Class used to store the results from a battle*/
class CombatResult{
public:
    CombatResult(const size_t & _playerCasualties, const size_t & _raiderCasualties);

    /** Number of player soldiers killed*/
    size_t playerCasualties;
    /** Number of raider soldiers killed*/
    size_t raiderCasualties;

    /** Number of surviving soldiers*/
    size_t remainingPlayer;
    /** Number of surviving raiders*/
    size_t remainingRaider;

    /** True if the battle was a draw (everyone died)*/
    bool draw;
};

/** @brief Class containing static methods needed for combat*/
class Combat{
public:
    /** Evaluates combat and returns CombatResult*/
    static CombatResult evaluateCombat(size_t playerSoldiers, size_t raiderSoldiers);
};
