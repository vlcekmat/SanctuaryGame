#include <string>
#include "../WinConditions/WinConditions.h"
#include "../GlobalEvents/GlobalEvents.h"
#include "../Action/Action.h"

/** Constant defining path to the winning conditions configuration file*/
#define ENDCONDITIONSJSON "./assets/GameParametres/EndConditions.json"
/** Constant defining path to the game world configuration file*/
#define GAMEWORLDJSON "./assets/GameParametres/GameWorld.json"
/** Constant defining path to the global events configuration file*/
#define EVENTSJSON "./assets/GameParametres/Events.json"
/** Constant defining path to the buildings configuration file*/
#define BUILDINGSJSON "./assets/GameParametres/Buildings.json"
/** Path to the actions configuration file*/
#define ACTIONSJSON "./assets/GameParametres/Actions.json"


#pragma once

using namespace std;

class JsonParser{
public:
    JsonParser();

    static void parseWinConditions(WinConditionsHandler & winConditionsHandler);

    static void parseGameWorld(string  & file_name, size_t & trees, size_t & rocks, size_t & animals, size_t & berries);

    static void parseGlobalEvents(EventPool & eventPool);

    static void parseBuildings(BuildingPool & buildingPool);

    static void parseActions(ActionPool & actionPool, EventHandler & eventHandler);

    virtual ~JsonParser();
};