#include "./WinConditions.h"

WinCondition::WinCondition() {}
bool WinCondition::checkCondition(GameState & game_state, shared_ptr<AI> ai) {
    return false;
}
WinCondition::~WinCondition() {}

// -----------------------------------------------------------------

ResourceWinCondition::ResourceWinCondition(const string & _resourceName, const size_t & _goalAmount): resourceName(_resourceName), goalAmount(_goalAmount){}

bool ResourceWinCondition::checkCondition(GameState &game_state, shared_ptr<AI> ai) {
    auto resourceIt = game_state.resources.find(resourceName);
    if (resourceIt == game_state.resources.end())
        return false;

    return resourceIt->second >= goalAmount;
}

ResourceWinCondition::~ResourceWinCondition(){}

// -----------------------------------------------------------------

PopulationWinCondition::PopulationWinCondition(const size_t & _goalAmount): goalAmount(_goalAmount) {}

bool PopulationWinCondition::checkCondition(GameState &game_state, shared_ptr<AI> ai) {
    return (game_state.people >= goalAmount);
}

PopulationWinCondition::~PopulationWinCondition() {}

// -----------------------------------------------------------------

RaiderDefeatWinCondition::RaiderDefeatWinCondition() {}

bool RaiderDefeatWinCondition::checkCondition(GameState &game_state, shared_ptr<AI> ai) {
    if (ai == nullptr)
        return false;
    auto aiState = ai->getState();

    if (aiState == nullptr)
        return false;

    return (aiState->settlements.empty());
}

RaiderDefeatWinCondition::~RaiderDefeatWinCondition() {}

// -----------------------------------------------------------------


WinConditionsHandler::WinConditionsHandler() {}

bool WinConditionsHandler::checkConditions(GameState &game_state, const shared_ptr<AI> & ai){
    for (const auto & condition : conditions){
        if (condition->checkCondition(game_state, ai))
            return true;
    }
    return false;
}

WinConditionsHandler::~WinConditionsHandler() {}


