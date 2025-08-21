#include "GameWorld.h"
#include "../JsonParser/JsonParser.h"

using namespace std;

GameWorld::GameWorld(){}
GameWorld::~GameWorld(){}

// right now initializing in the code, later will load from a file
void GameWorld::initalizeGameWorld(){

    // loads game_world parameters from the appropriate JSON file
    parseGameWorld(GAMEWORLDJSON, trees, rocks, animals, berries);

}

size_t GameWorld::modifyTrees( int count ){

    if (count < 0){
        if (count*(-1) > (int)trees)
            count = trees*(-1);

        cout << "\n\033[1;32m" << -(count) << " tree(s) have been cut down.\033[0m" << endl;
        if ((size_t)(count*(-1)) > trees)
            count = trees;
        trees += count;
        return (-1)*count;
    }

    else if (count > 0)
    {   
        cout << "\n\033[1;32m" << count << " tree(s) have grown up.\033[0m" << endl;
        trees += count;
        return count;
    }

    return count;
}

size_t GameWorld::modifyRocks( int count ){


    if (count < 0){
        if (count*(-1) > (int)rocks)
            count = rocks*(-1);

        cout << "\n\033[1;32m" << -(count) << " rock(s) have been mined out.\033[0m" << endl;
        if ((size_t)(count*(-1)) > rocks)
            count = rocks;
        rocks += count;
        return (-1)*count;
    }

    else if (count > 0)
    {
        cout << "\n\033[1;32m" << count << " rock(s) have been discovered.\033[0m" << endl;
        rocks += count;
        return count;
    }

    return count;
}

size_t GameWorld::modifyAnimals( int count ){

    if (count < 0){
        if (count*(-1) > (int)animals)
            count = animals*(-1);

        cout << "\n\033[1;32m" << -(count) << " animal(s) have been killed.\033[0m" << endl;
        if ((size_t)(count*(-1)) > animals)
            count = animals;
        animals += count;
        return (-1)*count;
    }

    else if (count > 0)
    {
        cout << "\n\033[1;32m" << count << " animal(s) have been born.\033[0m" << endl;
        animals += count;
        return count;
    }

    return count;
}

size_t GameWorld::modifyBerries( int count ){

    if (count < 0){
        if (count*(-1) > (int)berries)
            count = berries*(-1);
        cout << "\n\033[1;32m" << -(count) << " berries have been collected.\033[0m" << endl;
        if ((size_t)(count*(-1)) > berries)
            count = berries;
        berries += count;
        return (-1)*count;
    }

    else if (count > 0)
    {
        cout << "\n\033[1;32m" << count << " berries have grown.\033[0m" << endl;
        berries += count;
        return count;
    }

    return count;
}

void GameWorld::printGameWorld(){
    cout << "\nTREES: " << trees << endl;
    cout << "ROCKS: " << rocks << endl;
    cout << "ANIMALS: " << animals << endl;
    cout << "BERRIES: " << berries << endl;
    cout << endl;
}

void GameWorld::parseGameWorld(string file_name, size_t & trees, size_t & rocks, size_t & animals, size_t & berries){
    JsonParser::parseGameWorld(file_name, trees, rocks, animals, berries);
}
