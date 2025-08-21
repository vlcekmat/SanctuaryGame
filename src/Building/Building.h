#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <regex>
#include <fstream>
#include <string>
#include "../../libs/json.hpp"

#pragma once

using json = nlohmann::json;
using namespace std;

/** @brief Base class for all buildings
 * 
 *  Data loaded from Buildings.json are then used to define instances of this class
 * 
*/
class Building{

public:
    /** name of the building*/
    string name;

    Building();

    /** Maximum number of workers in this building*/
    size_t occupant_capacity;
    /** Minimum number of workers to apply the building's effect*/
    size_t minimum_workers;
    /** Number of people currently working in this building*/
    size_t current_workers;

    /** Set of resources needed to build this building*/
    set<pair<string, size_t>> cost;
    
    /** Name of the effect this building has and its value*/
    pair<string, int> effect;

    virtual ~Building();
};

/** @brief Class that will be later used for storing instances of Building*/
class BuildingPool
{
public:
    /** Pseudo-database of known buildings*/
    map<string, Building*> buildings;
    /** Constructor loads buildings from a json file and saves them to the pseudo-database*/
    BuildingPool();
    /** Frees allocated memory for buildings*/
    ~BuildingPool();
};

