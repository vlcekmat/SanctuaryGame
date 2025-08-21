#include <iostream>
#include <cstring>

#include "./EventHandler/EventHandler.h"
#include "./CommandHandler/CommandHandler.h"

#define GAME_NAME "The Harvest Guild"

using namespace std;

/*! @mainpage The Harvest Guild - building strategy game
 *
 * @section Rules Rules of the game
 * This game is text/command based. To show all available commands in the game, type "help".
 * 
 * In The Harvest Guild you become a leader of a small group of settlers, who are trying to survive in a new found land. To do so, they must gather resources to construct buildings. Buildings can have various effects, from collecting food, to providing more capacity for more villagers. If all people die or leave, it is game over. However, hunger is not the only threat in these lands, as raiders will do anything to prevent your progress and murder your people.
 * 
 * @subsection resources Resources
 * There are two main ways of collecting resources: by executing commands and by constructing a building.
 * 
 * To collect resources by using commands, simply type "harvest {resource_name}" this sends all villagers, that are not yet given a job in a building to collect the give resource
 * this command can be currently used to collect wood and stone, as well as animals and berries that provide food.
 * 
 * @subsection game_world Game World
 * Resources in the game are not unlimited, by using command "world" the player can print the current game world state. If, for example, the player decides to send all unemployed people to chop wood, but there are no trees left in the world, those workers just return empty handed.
 * 
 * @subsection buildings Buildings
 * In order to achieve more in the game, the player will need to construct buildings. If the player has enough resources, they can call the "build {building_name}" command, which constructs the specified building. All buildings have a minimal number of workers in the building in order to have an effect on the world. To assign an unemployed person to a building or unemploy a person from a building, use the "employ {building_index} {(-)number}".
 * 
 * After every turn all buildings' effects are evaluated.
 * 
 * @subsection events Events
 * To make the game less predictable, every turn is a random global event called. These events can have positive or negative impact on the player.
 *
 * @subsection combat Combat
 *
 * Combat can occur in two cases.
 *
 * 1) when the player is attacked by raiders
 * 2) when the player attacks raiders
 *
 * For both cases, the player must draft soldiers from their unemployed population. These soldiers serve both as defenders and attackers.
 *
 * @section customization Game Customization
 * The game can be customized and defined by the user. There are three parts of the game that can be manipulated:
 * 
 * 1) Game world - starting parameters of the game world, how many resources are available
 * 
 * 2) Buildings - definition of the buildings, what they cost, how many people can occupy them, etc. Player can define their own buildings.
 * 
 * 3) Events - the user can also modify the pool of events that are randomly called each round of the game
 *
 * 4) Winning conditions - the user can define their own winning conditions
 *
 * 5) Actions - custom commands that can be executed by the player
 *
 * All of those can be modified in their appropriate .json files located in /assets
 * 
 * @subsection effects List of effects currently usable in game definitions
 * 
 * modWood - Effect that modifies wood resources without chopping/seeding trees
 * modStone - Effect that modifies stone resources without mining out rocks
 * modTrees - Effect that modifies trees without affecting resources
 * modRocks - Effect that modifies rocks without affecting resources
 * modAnimals - Effect that modifies animals without affecting resources
 * modBerries - Effect that modifies berries without affecting resources
 * chopTrees - Effect that chops trees down and collects wood
 * mineRocks - Effect that mines rocks and collects stone
 * huntAnimals - Effect that hunts animals and collects food
 * gatherBerries - Effect that takes berries and collects food
 * housing - Effect that raises the population capacity
 * strangerArrives - Effect that raises population if there is capacity
 * killPeople - Effect that kills people
 * draft - Effect that drafts people to the army
 * undraft - Effect that undrafts people from the army
 *
 */

/** 
 * Start of the program, handles basic game cycle, as well as catches exceptions
*/
int main ( void ){
    GameState * game_state = nullptr;
    try{
        game_state = new GameState();
        EventHandler event_handler(*game_state, game_state->ai);
        CommandHandler command_handler(*game_state, event_handler);

        cout << "\n" << "\033[1;31m" << "WELCOME TO " << "\033[1;33m\n" << GAME_NAME << "\033[0m" << endl;
        cout << "\n" << "Type 'load {file_name}' to load an existing game" << endl;
        cout << "\n" << "Type 'new' to start a new game\n" << endl;

        bool load_print = false;
        bool terminateFlag = false;

        while (true){
            string choice;
            cin >> choice;

            if (choice == "new")
                break;
            else if (choice == "load"){
                if (command_handler.doCommand(choice) == 3){
                    terminateFlag = true;
                    break;
                }
                load_print = true;
                break;
            }
            cout << "\n" << "Command not found, try again" << endl;
        }



        // Main game cycle
        while ( true ){
            if (terminateFlag)
                break;

            if (load_print)
                load_print = false;
            else
                game_state->printGameState();
            
            if(!command_handler.readCommand())
                break;

            if (event_handler.doEveryTurn())
                break;

        }

        delete game_state;
        return 0;

    }
    catch (char const * exc){
        if (strcmp(exc, "JsonNotFoundException") == 0){
            cout << "Game definition .json files not found, please make sure there are game definition files Events.json, GameWorld.json and Buildings.json located in /assets/GameParametres." << endl;
            delete game_state;
            return 1;
        }
        else if (strcmp(exc, "InvalidJsonException") == 0){
            cout << "Game parameter file/s is/are invalid. Please check the syntax of files in the /assets/GameParameters/ folder" << endl;
            delete game_state;
            return 1;
        }
        else {
            cout << exc << endl;
            delete game_state;
            return 1;
        }
    }
    catch (string exc){
        cout << exc << endl;
        delete game_state;
        return 1;
    }
}
