#include "Effect.h"

using namespace std;

Effect::Effect(){}
Effect::~Effect(){}

// Resource modifying effects
// -------------------------------------------------------------------------------------------------------------------------
ModWood::ModWood( GameState & game_state ): g_state(game_state){
    effect_name = "modWood";
}
ModWood::~ModWood(){}
void ModWood::applyEffect(int value){
    g_state.resources.find("wood")->second += value;
}
// -------------------------------------------------------------------------------------------------------------------------
ChopTrees::ChopTrees( GameState & game_state ): g_state(game_state){
    effect_name = "chopTrees";
}
ChopTrees::~ChopTrees(){}
void ChopTrees::applyEffect(int value){
    if (value > 0){
        int trees_cut = g_state.game_world.modifyTrees( value*(-1) );
        g_state.resources.find("wood")->second += trees_cut * 2;
    }
}
// -------------------------------------------------------------------------------------------------------------------------
MineRocks::MineRocks( GameState & game_state ): g_state(game_state){
    effect_name = "mineRocks";
}
MineRocks::~MineRocks(){}
void MineRocks::applyEffect(int value){
    if (value > 0){
        int rocks_mined = g_state.game_world.modifyRocks( value*(-1) );
        g_state.resources.find("stone")->second += rocks_mined * 2;
    }
}
// -------------------------------------------------------------------------------------------------------------------------
ModStone::ModStone( GameState & game_state ): g_state(game_state){
    effect_name = "modStone";
}
ModStone::~ModStone(){}
void ModStone::applyEffect(int value){
    g_state.resources.find("stone")->second += value;
}

// Other effects
// -------------------------------------------------------------------------------------------------------------------------
ModTrees::ModTrees(GameState & game_state): g_state(game_state){
    effect_name = "modTrees";
}
ModTrees::~ModTrees(){}

void ModTrees::applyEffect(int value){
    g_state.game_world.modifyTrees(value);
}
// -------------------------------------------------------------------------------------------------------------------------
ModRocks::ModRocks(GameState & game_state): g_state(game_state){
    effect_name = "modRocks";
}
ModRocks::~ModRocks(){}

void ModRocks::applyEffect(int value){
    g_state.game_world.modifyRocks(value);
}
// -------------------------------------------------------------------------------------------------------------------------
ModAnimals::ModAnimals(GameState & game_state): g_state(game_state){
    effect_name = "modAnimals";
}
ModAnimals::~ModAnimals(){}

void ModAnimals::applyEffect(int value){
    g_state.game_world.modifyAnimals(value);
}
// -------------------------------------------------------------------------------------------------------------------------
HuntAnimals::HuntAnimals(GameState & game_state): g_state(game_state){
    effect_name = "huntAnimals";
}
HuntAnimals::~HuntAnimals(){}

void HuntAnimals::applyEffect(int value){
    int number_hunted = g_state.game_world.modifyAnimals(value*(-1));
    g_state.food += number_hunted * ANIMALFOODVALUE;
}
// -------------------------------------------------------------------------------------------------------------------------
GatherBerries::GatherBerries(GameState & game_state): g_state(game_state){
    effect_name = "gatherBerries";
}
GatherBerries::~GatherBerries(){}

void GatherBerries::applyEffect(int value){
    int number_hunted = g_state.game_world.modifyBerries(value*(-1));
    g_state.food += number_hunted * BERRYFOODVALUE;
}
// -------------------------------------------------------------------------------------------------------------------------
ModBerries::ModBerries(GameState & game_state): g_state(game_state){
    effect_name = "modBerries";
}
ModBerries::~ModBerries(){}

void ModBerries::applyEffect(int value){
    g_state.game_world.modifyBerries(value);
}
// -------------------------------------------------------------------------------------------------------------------------
Housing::Housing( GameState & game_state ): g_state(game_state){
    effect_name = "housing";
}
Housing::~Housing(){}

void Housing::applyEffect(int value){
    g_state.population_capacity += value;
}
// -------------------------------------------------------------------------------------------------------------------------
StrangerArrives::StrangerArrives( GameState & game_state ): g_state(game_state){
    effect_name = "strangerArrives";
}
StrangerArrives::~StrangerArrives(){}
void StrangerArrives::applyEffect(int value){
    if (value > 0){
        if ((g_state.population_capacity - g_state.people) >= (size_t)value){
            g_state.people += value;
            g_state.unemployed_people += value;
            cout << "\033[1;32m" << value << " stranger(s) arrived and joined your settlement\033[0m" << endl;
        }
        else 
            cout << "\033[1;31m" << value << " stranger(s) arrived, but you don't have enough housing for them\033[0m" << endl;
    }
}
// -------------------------------------------------------------------------------------------------------------------------
KillPeople::KillPeople( GameState & game_state ): g_state(game_state){
    effect_name = "killPeople";
}
KillPeople::~KillPeople(){}
void KillPeople::applyEffect(int value){

    if ((size_t)value > g_state.people){
        value = g_state.people;
    }

    cout << "\033[1;31m" << value << " people died\033[0m" << endl;
    g_state.killPeople(value);
}
// -------------------------------------------------------------------------------------------------------------------------
DestroyBuildings::DestroyBuildings( GameState & game_state ): g_state(game_state){
    effect_name = "destroyBuildings";
}
DestroyBuildings::~DestroyBuildings(){}
void DestroyBuildings::applyEffect(int value){

    if (value > 0){
        
        if ((size_t)value > g_state.buildings.size())
            value = g_state.buildings.size();

        // for each iteration pick a random building index to destroy
        for (int i = 0; i < value; i ++){
            size_t index = rand() % (g_state.buildings.size());

            // get to the index
            auto build_it = g_state.buildings.begin();
            while (index != 0){
                build_it ++;
                index --;
            }

            // move the building's current workers to unemployed people
            g_state.unemployed_people += (*build_it)->current_workers;

            // and finally erase the building
            delete (*build_it);
            g_state.buildings.erase(build_it);
        }        
        cout << "\033[1;31m" << value << " buildings collapsed\033[0m" << endl;
    }

    
}
// -------------------------------------------------------------------------------------------------------------------------
Draft::Draft(GameState &game_state): g_state(game_state){
    effect_name = "draft";
}
Draft::~Draft(){}
void Draft::applyEffect(int value) {
    if (value <= 0 || g_state.people == 0){
        cout << "No people were drafted." << endl;
        return;
    }

    if (g_state.unemployed_people < (size_t)value)
        value = (int)g_state.unemployed_people;

    g_state.soldiers += value;
    g_state.unemployed_people -= value;

    cout << value << " people were drafted" << endl;
}
// -------------------------------------------------------------------------------------------------------------------------
Undraft::Undraft(GameState &game_state): g_state(game_state){
    effect_name = "undraft";
}
Undraft::~Undraft(){}
void Undraft::applyEffect(int value) {
    if (value <= 0 || g_state.soldiers == 0){
        cout << "No people were undrafted." << endl;
        return;
    }

    if (g_state.soldiers < (size_t)value)
        value = (int)g_state.soldiers;

    g_state.unemployed_people += value;
    g_state.soldiers -= value;

    cout << value << " people were undrafted" << endl;
}
// -------------------------------------------------------------------------------------------------------------------------
