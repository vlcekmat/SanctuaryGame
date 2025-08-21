#include <iostream>
#include <fstream>
#include <regex>

#pragma once

using namespace std;

/** @brief Class defining and operating with the game world - entities outside of the player's settlement*/
class GameWorld{

public:
    GameWorld();

    // world properties
    size_t trees;
    size_t rocks;
    size_t animals;
    size_t berries;

    /** Set initial values according to GameWorld.json*/
    void initalizeGameWorld();

    /** Adds or removes trees in the world and returns how many have been added/removed*/
    size_t modifyTrees( int count );
    /** Adds or removes rocks in the world and returns how many have been added/removed*/
    size_t modifyRocks( int count );
    /** Adds or removes animals in the world and returns how many have been added/removed*/
    size_t modifyAnimals( int count );
    /** Adds or removes berries in the world and returns how many have been added/removed*/
    size_t modifyBerries ( int count );

    /** This is called by a command, it shows current world state to the player*/
    void printGameWorld();

    /** Method that loads starting game world definiton from the jsonm file*/
    void parseGameWorld(string file_name, size_t & trees, size_t & rocks, size_t & animals, size_t & berries);

    virtual ~GameWorld();
};