#include <iostream>
#include <map>
#include <list>
#include "../Building/Building.h"
#include "../GameWorld/GameWorld.h"
#include "../AI/AI.h"

#pragma once

using namespace std;

/** @brief Class responsible for player's data, data here will be used to create a binary save file*/
class GameState{

public:
    /** Initializes implicit GameState values*/
    GameState();

    /** Frees allocated memory*/
    ~GameState();

    /** Variable to help interact with the game world*/
    GameWorld game_world;

    /** Stores buildings that can be built*/
    BuildingPool building_pool;

    /** Overall number of villagers*/
    size_t people;
    /** Number of villagers who are not assigned to any building and can be used to harvest resources by commands*/
    size_t unemployed_people;
    /** Number of villagers who are assigned as soldiers, they will defend and attack raiders*/
    size_t soldiers;
    /** Amount of food the settlement has, without food, villagers starve*/
    size_t food;
    /** I wanted to implement happiness, but I didn't really see how it would fit within the game, 
     * so I decided to leave it here if I decide to work on the game futher, however right now, it does nothing */
    size_t happiness;
    /** Max number of villagers there can be in the village */
    size_t population_capacity;

    shared_ptr<AI> ai;

    /** Resources used for building*/
    map<string, size_t> resources;
    /** Constructed buildings*/
    list<Building *> buildings;

    void killPeople( int count );

    bool addResources( string name, int count );

    void addBuilding( string name, size_t cur_workers );

    void printGameState();
    void printBuildings();
    
    bool loadSaveFile( string file_name );
    void saveFile( string file_name );

    bool checkResources( set<pair<string, size_t>> to_check );
    void removeResources( set<pair<string, size_t>> to_remove );

};