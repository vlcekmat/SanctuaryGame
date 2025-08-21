#include "EffectHandler.h"

using namespace std;

EffectHandler::EffectHandler(GameState & game_state) : g_state(game_state) {

    ModWood * mod_wood = new ModWood(g_state);
    effectPool.insert( {mod_wood->effect_name, mod_wood} );

    ChopTrees * chop_trees = new ChopTrees(g_state);
    effectPool.insert( {chop_trees->effect_name, chop_trees} );

    ModStone * mod_stone = new ModStone(g_state);
    effectPool.insert( {mod_stone->effect_name, mod_stone} );

    MineRocks * mine_rocks = new MineRocks(g_state);
    effectPool.insert( {mine_rocks->effect_name, mine_rocks} );

    ModTrees * mod_trees = new ModTrees(g_state);
    effectPool.insert( {mod_trees->effect_name, mod_trees} );

    ModRocks * mod_rocks = new ModRocks(g_state);
    effectPool.insert( {mod_rocks->effect_name, mod_rocks} );

    ModAnimals * mod_animals = new ModAnimals(g_state);
    effectPool.insert( {mod_animals->effect_name, mod_animals} );

    HuntAnimals * hunt_animals = new HuntAnimals(g_state);
    effectPool.insert( {hunt_animals->effect_name, hunt_animals} );

    ModBerries * mod_berries = new ModBerries(g_state);
    effectPool.insert( {mod_berries->effect_name, mod_berries} );

    GatherBerries * gather_berries = new GatherBerries(g_state);
    effectPool.insert( {gather_berries->effect_name, gather_berries} );

    Housing * housing = new Housing(g_state);
    effectPool.insert( {housing->effect_name, housing} );

    StrangerArrives * stranger_arrives = new StrangerArrives(g_state);
    effectPool.insert( {stranger_arrives->effect_name, stranger_arrives} );

    KillPeople * kill_people = new KillPeople(g_state);
    effectPool.insert( {kill_people->effect_name, kill_people} );

    DestroyBuildings * destroy_buildings = new DestroyBuildings(g_state);
    effectPool.insert( {destroy_buildings->effect_name, destroy_buildings} );

    Draft * draft = new Draft(g_state);
    effectPool.insert( {draft->effect_name, draft} );

    Undraft * undraft = new Undraft(g_state);
    effectPool.insert( {undraft->effect_name, undraft} );
}

void EffectHandler::callEffect(string name, int value, int multiplier){
    auto eff_it = effectPool.find(name);

    if (eff_it == effectPool.end()){
        if (name != "nothing")
            cout << "Effect: " << name << " does not exist" << endl;
    }
    else {
        if(multiplier == 0)
            multiplier = 1;
        eff_it->second->applyEffect(value*multiplier);
    }
}

EffectHandler::~EffectHandler(){

    auto ef_pool_it = effectPool.begin();

    while ( ef_pool_it != effectPool.end() ){
        delete (ef_pool_it->second);
        ef_pool_it ++;
    }

    effectPool.clear();
}
