
#include <string>
#include "../GameState/GameState.h"
#include "../Action/Action.h"

using namespace std;

/** Constant defining how much food do we get from one animal using commands*/
#define ANIMALFOODVALUEC 5
/** Constant defining how much food do we get from one berry using commands*/
#define BERRYFOODVALUEC 2
/** Constant defining how effective are unemployed people (workers who are used by commands)*/
#define UNEMPLOYEDEFFECTIVITY 2

#pragma once

/** @brief Base abstract class for all commands, this is where polymorfism is used*/
class Command{

public:
    Command();

    /** How the command is supposded to be written in the terminal*/
    string syntax;
    /** Description of the command that shows after calling the "help" command*/
    string description;
    /** Method that applies effect of the command, it returns int instead of bool, 
     * because I use 3 states: 
     * 0 = command successful and ends turn, 
     * 1 = command encountered an error, doesn't end turn, 
     * 2 = command successful and doesn't end turn
     * 3 = exits application*/
    virtual int executeCommand() = 0;

    virtual ~Command();
};

// -------------------------------------------------------------------------------------------------------------------------

// program management commands

/** @brief Command that prints all possible commands and their description to the console*/
class ExitCommand : public Command{
public:

    ExitCommand();

    virtual int executeCommand() override;
};

// -------------------------------------------------------------------------------------------------------------------------

// info commands

/** @brief Command that prints all possible commands and their description to the console*/
class HelpCommand : public Command{

public:

    HelpCommand( map<string, Command*> & commands_map );

    map<string, Command*> & all_commands;
    
    virtual int executeCommand() override;

};

// -------------------------------------------------------------------------------------------------------------------------

/** @brief Command that prints the current world state to the console*/
class WorldCommand : public Command{

public:

    WorldCommand(GameState & game_state);
    GameState & g_state;

    virtual int executeCommand() override;
};

// -------------------------------------------------------------------------------------------------------------------------

/** @brief Command that prints available buildings and their costs to the console*/
class BuildingsCommand : public Command{

public:

    BuildingsCommand(GameState & game_state);
    GameState & g_state;

    virtual int executeCommand() override;
};

// -------------------------------------------------------------------------------------------------------------------------

/** @brief Command that prints settlements built by AI*/
class SettlementsCommand : public Command{

public:

    SettlementsCommand(GameState & game_state);
    GameState & g_state;

    virtual int executeCommand() override;
};

// -------------------------------------------------------------------------------------------------------------------------

// harvest commands

/** @brief Command that sends unemployed population to harvest the specified resource*/
class HarvestCommand : public Command{

public:
    HarvestCommand(GameState & game_state);
    GameState & g_state;

    virtual int executeCommand() override;
};


// -------------------------------------------------------------------------------------------------------------------------

// building commands

/** @brief Command that builds the specified building for its required resources*/
class BuildCommand : public Command{

public:

    BuildCommand(GameState & game_state);
    GameState & g_state;

    virtual int executeCommand() override;
};

// -------------------------------------------------------------------------------------------------------------------------

/** @brief Command that destroys specified constructed building*/
class DestroyCommand : public Command{

public:

    DestroyCommand(GameState & game_state);
    GameState & g_state;

    virtual int executeCommand() override;
};

// -------------------------------------------------------------------------------------------------------------------------

// other commands

/** @brief Command that employs specified number of people in the specified building*/
class EmployCommand : public Command{

public:

    EmployCommand(GameState & game_state);
    GameState & g_state;

    virtual int executeCommand() override;
};

// -------------------------------------------------------------------------------------------------------------------------

/** @brief Command that lets the player attack the raider settlements*/
class AttackCommand : public Command{

public:

    AttackCommand(GameState & game_state);
    GameState & g_state;

    virtual int executeCommand() override;

};

// -------------------------------------------------------------------------------------------------------------------------

/** @brief Command that ends turn without doing anything else*/
class WaitCommand : public Command{

public:

    WaitCommand();

    virtual int executeCommand() override;

};

// -------------------------------------------------------------------------------------------------------------------------

/** @brief Command saves current game state into a file specified by the argument*/
class SaveCommand : public Command{

public:

    SaveCommand(GameState & game_state);
    GameState & g_state;

    virtual int executeCommand() override;
};

// -------------------------------------------------------------------------------------------------------------------------

/** @brief Command loads game from the path specified in the argument*/
class LoadCommand : public Command{

public:

    LoadCommand(GameState & game_state);
    GameState & g_state;

    virtual int executeCommand() override;
};

/** @brief Command class that is calling an action defined in ActionsWithInvalidJson.json*/
// -------------------------------------------------------------------------------------------------------------------------
class ActionCommand : public Command{

public:

    ActionCommand();

    virtual int executeCommand() override;

    shared_ptr<Action> action;
};