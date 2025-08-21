#include <iostream>
#include <string>
#include <memory>
#include "../GameState/GameState.h"
#include "../AI/AI.h"
#include "../../libs/json.hpp"

#pragma once

using namespace std;
using json = nlohmann::json;

/** @brief Base class for all Winning Conditions
 *
 *  If winning conditions are fulfilled, the game ends with a victory
 *
*/
class WinCondition{
public:
    WinCondition();

    /** Checks if the winning condition is fulfilled*/
    virtual bool checkCondition(GameState & game_state, shared_ptr<AI> ai);

    virtual ~WinCondition();
};

/** @brief Type of winning condition that checks if a certain amount of a resource is reached*/
class ResourceWinCondition : public WinCondition{
public:
    ResourceWinCondition(const string & _resourceName, const size_t & _goalAmount);

    virtual bool checkCondition (GameState & game_state, shared_ptr<AI> ai) override;

    virtual ~ResourceWinCondition();
private:
    string resourceName;
    size_t goalAmount;
};

/** @brief Type of winning condition that checks if a certain amount of a population is reached*/
class PopulationWinCondition : public WinCondition{
public:
    PopulationWinCondition(const size_t & _goalAmount);

    virtual bool checkCondition (GameState & game_state, shared_ptr<AI> ai) override;

    virtual ~PopulationWinCondition();
private:
    size_t goalAmount;
};

/** @brief Type of winning condition that checks if raiders are defeated*/
class RaiderDefeatWinCondition : public WinCondition{
public:
    RaiderDefeatWinCondition();

    virtual bool checkCondition (GameState & game_state, shared_ptr<AI> ai) override;

    virtual ~RaiderDefeatWinCondition();
};

/** @brief Wrapper class that stores loaded conditions and checks if they are fulfilled*/
class WinConditionsHandler{
public:
    WinConditionsHandler();

    virtual bool checkConditions(GameState &game_state, const shared_ptr<AI> & ai);

    virtual ~WinConditionsHandler();

    set<unique_ptr<WinCondition>> conditions;

};