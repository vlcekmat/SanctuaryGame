#include "../../libs/json.hpp"
#include "./JsonParser.h"
#include <fstream>

using json = nlohmann::json;

JsonParser::JsonParser() {}
JsonParser::~JsonParser() {}

void JsonParser::parseWinConditions(WinConditionsHandler & winConditionsHandler) {
    if (ifstream(ENDCONDITIONSJSON)){
        ifstream file;
        file.open( ENDCONDITIONSJSON, ios::in );

        json jsonData;
        try{
            jsonData = json::parse(file);

            // append resource win conditions
            if (!jsonData["resource_end_conditions"].empty()){
                for (auto & el : jsonData["resource_end_conditions"]){
                    winConditionsHandler.conditions.insert(make_unique<ResourceWinCondition>(el["resource"], el["goal_amount"]));
                }
            }

            // append population win conditions
            if (!jsonData["population_goal"].empty() && !jsonData["population_goal"]["enabled"].empty() && jsonData["population_goal"]["enabled"] == true && !jsonData["population_goal"]["goal_amount"].empty() ){
                winConditionsHandler.conditions.insert(make_unique<PopulationWinCondition>(jsonData["population_goal"]["goal_amount"]));
            }

            // append raiders destroyed win conditions
            if (!jsonData["raiders_destroyed_goal_enabled"].empty() && jsonData["raiders_destroyed_goal_enabled"] == true){
                winConditionsHandler.conditions.insert(make_unique<RaiderDefeatWinCondition>());
            }

        }
        catch(nlohmann::json_abi_v3_11_2::detail::parse_error & e){
            file.close();
            throw "InvalidJsonException";
        }
        catch(nlohmann::json_abi_v3_11_2::detail::type_error & e){
            file.close();
            throw "InvalidJsonException";
        }
        file.close();
    }
    else {
        throw "JsonNotFoundException";
    }
}

void JsonParser::parseGameWorld(string & file_name, size_t & trees, size_t & rocks, size_t & animals, size_t & berries) {
    if (ifstream(file_name)){
        ifstream file;
        file.open( file_name, ios::in );

        json jsonData;
        try{
            jsonData = json::parse(file);

            if (!jsonData["trees"].empty()){
                trees = jsonData["trees"];
            } else {
                string error = "Trees data not found: ";
                error += GAMEWORLDJSON;
                throw error;
            }

            if (!jsonData["rocks"].empty()){
                rocks = jsonData["rocks"];
            } else {
                string error = "Rocks data not found: ";
                error += GAMEWORLDJSON;
                throw error;
            }

            if (!jsonData["animals"].empty()){
                animals = jsonData["animals"];

            } else {
                string error = "Animals data not found: ";
                error += GAMEWORLDJSON;
                throw error;
            }

            if (!jsonData["berries"].empty()){
                berries = jsonData["berries"];

            } else {
                string error = "Berries data not found: ";
                error += GAMEWORLDJSON;
                throw error;
            }
        }
        catch(nlohmann::json_abi_v3_11_2::detail::parse_error & e){
            file.close();
            throw "InvalidJsonException";
        }
        catch(nlohmann::json_abi_v3_11_2::detail::type_error & e){
            file.close();
            throw "InvalidJsonException";
        }

        file.close();

    }
    else {
        throw "JsonNotFoundException";
    }
}

void JsonParser::parseGlobalEvents(EventPool & eventPool) {
    if (ifstream(EVENTSJSON)){
        ifstream file;
        file.open(EVENTSJSON, ios::in);

        json jsonData;
        try{
            jsonData = json::parse(file);

            for (auto & el : jsonData["events"]){

                if (el["name"].empty() || el["probability"].empty()){
                    cout << "Invalid event definition" << endl;
                }
                else {
                    GlobalEvent * newEvent = new GlobalEvent();
                    newEvent->name = el["name"];
                    newEvent->probability = el["probability"];
                    for (auto & [key, value] : el["effect"].items()){
                        newEvent->effect.first = key;
                        newEvent->effect.second = value;
                    }
                    eventPool.event_vector.push_back(newEvent);
                }
            }
        }
        catch(nlohmann::json_abi_v3_11_2::detail::parse_error & e){
            file.close();
            throw "InvalidJsonException";
        }
        catch(nlohmann::json_abi_v3_11_2::detail::type_error & e){
            file.close();
            throw "InvalidJsonException";
        }


        file.close();
    }
    else
        throw "JsonNotFoundException";
}

void JsonParser::parseBuildings(BuildingPool & buildingPool) {
    if (ifstream(BUILDINGSJSON)){
        ifstream file;
        file.open( BUILDINGSJSON, ios::in );

        json jsonData;
        try{
            jsonData = json::parse(file);

            for( auto & el: jsonData["buildings"] ) {
                Building * new_building = new Building();

                if (el["name"].empty() || el["occupant_capacity"].empty() || el["minimum_workers"].empty()){
                    cout << "Invalid building definition";
                    if (!el["name"].empty())
                        cout << ": " << el["name"];

                    cout << endl;
                }

                new_building->name = el["name"];
                new_building->occupant_capacity = el["occupant_capacity"];
                new_building->minimum_workers = el["minimum_workers"];

                set<pair<string, size_t>> buildingCost;
                for (auto & costRecord : el["cost"]){
                    for (auto & [key, value] : costRecord.items()){
                        pair<string, size_t> to_append = {key, value};
                        buildingCost.insert(to_append);
                    }
                }
                new_building->cost = buildingCost;

                pair<string, int> buildingEffect;
                for (auto & [key, value] : el["effect"].items()){
                    buildingEffect = {key, value};
                }
                new_building->effect = buildingEffect;

                pair<string, Building*> building_record;
                building_record.first = new_building->name;
                building_record.second = new_building;

                if (buildingPool.buildings.find(new_building->name) == buildingPool.buildings.end()){
                    buildingPool.buildings.insert(building_record);
                }
                else {
                    delete new_building;
                }
            }

        }
        catch(nlohmann::json_abi_v3_11_2::detail::parse_error & e){
            file.close();
            throw "InvalidJsonException";
        }
        catch(nlohmann::json_abi_v3_11_2::detail::type_error & e){
            file.close();
            throw "InvalidJsonException";
        }

        file.close();

    }else{throw "JsonNotFoundException";}

}

void JsonParser::parseActions(ActionPool & actionPool, EventHandler & eventHandler) {
    if (ifstream(ACTIONSJSON)) {
        ifstream file;
        file.open(ACTIONSJSON, ios::in);

        json jsonData;
        try{
            jsonData = json::parse(file);

            for (auto & el : jsonData["actions"]) {
                // load command info
                if (!el["command"].empty() && el["command"]["syntax"].is_string() && el["command"]["description"].is_string()){
                    shared_ptr<Action> newAction = make_shared<Action>(eventHandler);
                    newAction->syntax = el["command"]["syntax"];
                    newAction->description = el["command"]["description"];

                    // load parameters
                    string newDescription;
                    for (auto & par : el["command"]["parameters"]){
                        newDescription += '{';
                        newDescription += par["name"];
                        newDescription += "} ";
                    }
                    newDescription += "- ";
                    newDescription += newAction->description;
                    newAction->description = newDescription;

                    // load effects
                    for (auto & ef : el["effects"]){

                        for (auto & it : ef.items()){
                            newAction->effects.insert(it.key());
                            if (it.value().is_string())
                                newAction->parameterMap.emplace(it.key(), it.value());
                            else if (it.value().is_number())
                                newAction->staticParameters.emplace(it.key(), it.value());
                        }
                    }

                    actionPool.actions.insert(newAction);
                }
            }
        }
        catch(nlohmann::json_abi_v3_11_2::detail::parse_error & e){
            file.close();
            throw "InvalidJsonException";
        }
        catch(nlohmann::json_abi_v3_11_2::detail::type_error & e){
            file.close();
            throw "InvalidJsonException";
        }

        file.close();

    }
    else {
        throw "JsonNotFoundException";
    }
}