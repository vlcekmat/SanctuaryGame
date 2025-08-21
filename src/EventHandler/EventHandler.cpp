#include "EventHandler.h"
#include "../JsonParser/JsonParser.h"

EventHandler::EventHandler(GameState & game_state, shared_ptr<AI> & _ai) : g_state(game_state), ai(_ai){
    eff_han = new EffectHandler(g_state);
    winConditionsHandler = make_unique<WinConditionsHandler>();

    try{
        JsonParser::parseGlobalEvents(event_pool);
        JsonParser::parseWinConditions(*winConditionsHandler);
    }
    catch(...){
        delete eff_han;
        throw "InvalidJsonException";
    }
}

bool EventHandler::doEveryTurn(){

    // reduce food by population and starve if not enough
    if (g_state.food < g_state.people){
        
        if (g_state.people - g_state.food > 0)
            cout << "\033[1;31mStarvation! " << (g_state.people - g_state.food) << " people died of hunger!\033[0m" << endl;

        // kill people who didn't eat
        g_state.killPeople(g_state.people - g_state.food);
        
        // check losing conditions
        if (g_state.people <= 0){
            cout << "\n\033[1;31mGAME OVER, EVERYONE IS GONE\033[0m" << endl;
            return true;
        }

        g_state.food = 0;
    }
    else 
        g_state.food -= g_state.people;

    // apply building effects and recalculate population capacity
    g_state.population_capacity = 1;
    auto build_it = g_state.buildings.begin();
    while ( build_it != g_state.buildings.end() ){
        string eff_name = (*build_it)->effect.first;
        int eff_value = (*build_it)->effect.second;

        if ((*build_it)->current_workers >= (*build_it)->minimum_workers)
            // effect value is multiplied by the number of cuurent workers
            eff_han->callEffect(eff_name, eff_value, ((*build_it)->current_workers));

        build_it ++;
    }

    // check if people still have somewhere to live
    if ( g_state.population_capacity < g_state.people ){
        int difference = g_state.people - g_state.population_capacity;
        g_state.killPeople(difference);

        cout << "\033[1;31m" << difference << " people don't have anywhere to live and left the settlement\033[0m" << endl;

        // check losing conditions again
        if (g_state.people <= 0){
            cout << "\n\033[1;31mGAME OVER, EVERYONE IS GONE\033[0m" << endl;
            return true;
        }
    }

    callRandomEvent();

    // check winning conditions
    if (winConditionsHandler->checkConditions(g_state, ai)){
        cout << "\n\033[1;32mCONGRATULATIONS, YOU WON\033[0m" << endl;
        return true;
    }

    // check losing conditions again
    if (g_state.people <= 0){
        cout << "\n\033[1;31mGAME OVER, EVERYONE IS GONE\033[0m" << endl;
        return true;
    }

    bool combatFlag = false;
    size_t attackingVillageIndex = 0;

    // AI's turn
    auto aiState = ai->getState();
    if (aiState->population > 0){
        ai->makeDecision(combatFlag, attackingVillageIndex);
    }
    else {
        cout << "AI: All raiders are gone" << endl;
    }

    // check combat
    if (combatFlag){
       // get the chosen settlement
       for (auto & settlement : aiState->settlements){
           if (attackingVillageIndex == 0){
               auto combatResult = Combat::evaluateCombat(g_state.soldiers, RAID_THRESHOLD - 1);
               g_state.soldiers -= combatResult.playerCasualties;
               g_state.people -= combatResult.playerCasualties;
               settlement->soldiers -= combatResult.raiderCasualties;

               if (combatResult.remainingRaider > 0){
                   eff_han->callEffect("killPeople", 1, 1);
                   eff_han->callEffect("destroyBuildings", 1, 1);
               }
               break;
           }
           else
               attackingVillageIndex --;
       }
    }

    ai->printState();

    // check winning conditions
    if (winConditionsHandler->checkConditions(g_state, ai)){
        cout << "\n\033[1;32mCONGRATULATIONS, YOU WON\033[0m" << endl;
        return true;
    }

    // check losing conditions again
    if (g_state.people <= 0){
        cout << "\n\033[1;31mGAME OVER, EVERYONE IS GONE\033[0m" << endl;
        return true;
    }

    return false;
}

void EventHandler::callRandomEvent(){

    // This part of code was written with the help of this Stack Overflow question: 
    // https://stackoverflow.com/questions/69873685/how-to-randomly-pick-element-from-an-array-with-different-probabilities-in-c

    // load probabilities for discrete distribution
    list<int> probabilities;
    for (GlobalEvent * event : event_pool.event_vector){
        probabilities.push_back(event->probability);
    }

    mt19937 gen(random_device{}());


    discrete_distribution<size_t> distribution(probabilities.begin(), probabilities.end());

    auto randomized_index = distribution(gen);

    eff_han->callEffect(
        event_pool.event_vector[randomized_index]->effect.first,
        event_pool.event_vector[randomized_index]->effect.second,
        1
    );

    cout << "\n\033[1;33mEvent: " << event_pool.event_vector[randomized_index]->name << "\033[0m\n" << endl;
}

EventHandler::~EventHandler(){
    delete eff_han;
}