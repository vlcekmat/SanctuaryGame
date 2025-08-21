#include <iostream>
#include <map>
#include "GameState.h"
#include "../JsonParser/JsonParser.h"

GameState::GameState(){

    JsonParser::parseBuildings(building_pool);

    people = 1;
    unemployed_people = people;
    soldiers = 0;
    food = 10;
    happiness = 100;

    population_capacity = 1;

    resources.insert( {"wood", 0} );
    resources.insert( {"stone", 0} );

    game_world.initalizeGameWorld();

    ai = make_shared<AI>();

}

GameState::~GameState(){ 
    for ( Building * b : buildings ){
        if ( b != nullptr )
            delete b;
        b = nullptr;
    }
}

bool GameState::addResources(string name, int count){
    auto res_it = resources.find(name);

    if ( res_it == resources.end() )
        return 1;
    
    res_it->second += count;
    cout << "\nHarvested " << count << " " << name << "\n" << endl; 

    return 0;
}

void GameState::addBuilding(string name, size_t cur_workers = 0){

    auto b_pool_it = building_pool.buildings.find(name);

    if (b_pool_it == building_pool.buildings.end()){
        string error = "This savefile includes unknown building, unable to load: ";
        error += name;
        throw error;
    }

    Building * new_building = new Building();

    new_building->name = b_pool_it->second->name;
    new_building->occupant_capacity = b_pool_it->second->occupant_capacity;
    new_building->minimum_workers = b_pool_it->second->minimum_workers;
    new_building->cost = b_pool_it->second->cost;
    new_building->effect = b_pool_it->second->effect;

    new_building->current_workers = cur_workers;

    buildings.push_back(new_building);
}

void GameState::killPeople(int count){
    people -= count;

    // remove (count) random people from occupied buildings
    int buildings_count = buildings.size();
    for ( int i = 0; i < count; i++ ){
        int random_index = rand()%(buildings_count + 1);

        if (random_index == buildings_count){
            if (unemployed_people > 0)
                unemployed_people --;
            else if (soldiers > 0)
                soldiers --;
            else
                i --;
        }
        else {
            auto build_it = buildings.begin();
            while (random_index != 0)
            {
                build_it ++;
                random_index --;
            }

            if ((*build_it)->current_workers > 0)
                (*build_it)->current_workers --;
            else
                i --;
            
        }

    }
}

void GameState::printBuildings(){

    auto b_it = buildings.begin();

    size_t building_index = 0;

    while (b_it != buildings.end() ){
        cout << "   -" << (*b_it)->name << " " << (*b_it)->current_workers << "/" << (*b_it)->occupant_capacity << " [" << building_index << "]" << endl;
        b_it ++;
        building_index ++;
    }

}

void GameState::printGameState(){

    cout << "--------------------------" << endl;
    
    // Print basic info
    cout << "\033[1;35m" << "\nMAIN INFORMATION:" << "\033[0m" << endl;
    cout << "   -Population: " << people << "/" << population_capacity << endl;
    cout << "   -Unemployed Population: " << unemployed_people << endl;
    cout << "   -Assigned soldiers: " << soldiers << endl;
    cout << "   -Food: " << food << endl;

    // Print buildings
    if( buildings.size() > 0 )
        cout << "\033[1;35m" << "\nBUILDINGS:" << "\033[0m" << endl;
    printBuildings();

    // Print resources
    cout << "\033[1;35m" << "\nRESOURCES:" << "\033[0m" << endl;
    auto res_it = resources.begin();
    while ( res_it != resources.end() ){
        cout << "   -" << res_it->first << ": " << res_it->second << endl;
        res_it ++;
    }
    cout << endl;

}

bool GameState::checkResources( set<pair<string, size_t>> to_check ){

    auto set_it = to_check.begin();

    while ( set_it != to_check.end() ){

        auto found_item = resources.find( set_it->first );

        if ( found_item == resources.end() || found_item->second < set_it->second){
            return false;
        }

        set_it ++;
    }

    return true;
}

void GameState::removeResources( set<pair<string, size_t>> to_remove ){
    auto set_it = to_remove.begin();

    while ( set_it != to_remove.end() ){

        auto found_item = resources.find( set_it->first );

        found_item->second -= set_it->second;

        set_it ++;
    }
}

void GameState::saveFile( string file_name ){
    fstream file;
    file.open( file_name, ios::binary | ios::out );

    auto aiState = ai->getState();

    // save primitive info
    file 
    << people << "\n" 
    << unemployed_people << "\n"
    << soldiers << "\n"
    << food << "\n"
    << happiness << "\n" 
    << population_capacity << "\n"
    << game_world.animals << "\n" 
    << game_world.berries << "\n" 
    << game_world.trees << "\n" 
    << game_world.rocks << "\n"
    << aiState->population << "\n"
    << aiState->resources << "\n"
    << flush;

    // save resources info
    for ( pair<string, size_t> resource : resources ){
        file << resource.first << "\n" << resource.second << "\n" << flush;
    }

    // resources are dynamic, hence the separator \n:\n
    file << "\n:\n" << flush;

    // save buildings info
    for ( Building * building : buildings ){
        file 
        << building->name << "\n"
        << building->current_workers << "\n"
        << flush;
    }

    file << "\n:\n" << flush;

    // save settlements info
    for (const auto & settlement : aiState->settlements){
        file
        << settlement->soldiers << "\n"
        << flush;
    }

    file << "\n:\n" << flush;

    file.close();
}

bool GameState::loadSaveFile( string file_name ){
    for ( Building * b : buildings ){
        if ( b != nullptr )
            delete b;
        b = nullptr;
    }

    fstream file;

    auto aiState = ai->getState();

    if (fstream(file_name)){
        file.open( file_name, ios::binary | ios::in );

        // load primitive information
        file >> people;
        file >> unemployed_people;
        file >> soldiers;
        file >> food;
        file >> happiness;
        file >> population_capacity;

        file >> game_world.animals;
        file >> game_world.berries;
        file >> game_world.trees;
        file >> game_world.rocks;

        file >> aiState->population;
        file >> aiState->resources;

        // load resources
        resources.clear();
        while (true){
            string sep_filter;
            file >> sep_filter;

            if (file.eof() || sep_filter.empty()){
                cout << file_name << ": " << "Invalid file" << endl;
                return false;
            }

            if (sep_filter == ":")
                break;
            pair<string, size_t> res_to_load;
            res_to_load.first = sep_filter;
            file >> res_to_load.second;

            resources.insert(res_to_load);
        }

        // load buildings
        buildings.clear();
        while (true){
            string sep_filter;
            file >> sep_filter;

            if (file.eof() || sep_filter.empty()){
                cout << file_name << ": " << "Invalid file" << endl;
                return false;
            }

            if (sep_filter == ":")
                break;

            string building_name;
            size_t workers_count;

            building_name = sep_filter;
            file >> workers_count;

            this->addBuilding(building_name, workers_count);
        }

        // load raider settlements
        aiState->settlements.clear();
        while (true){
            string sep_filter;
            file >> sep_filter;

            if (file.eof() || sep_filter.empty()){
                cout << file_name << ": " << "Invalid file" << endl;
                return false;
            }

            if (sep_filter == ":")
                break;

            size_t soldierCount = std::stoul(sep_filter);

            aiState->settlements.push_back(make_shared<Settlement>(soldierCount));
        }

        file.close();
    }
    else {
        throw "File not found";
    }
    return true;
}