#include <map>
#include "../Commands/Commands.h"
#include "../EventHandler/EventHandler.h"

using namespace std;

#pragma once

/** @brief Class that reads commands written by player, validates and executes them */
class CommandHandler
{
private:
    /** Pseudo-database of all known commands*/
    map<string, Command*> commands;

    /** Stored actions*/
    unique_ptr<ActionPool> actionPool;

public:
    /** Constructror initializes all wanted commands into the handler's pseudo-database*/
    CommandHandler(GameState & game_state, EventHandler & event_handler);
    /** Reference to the current GameState, so the commands can influence it*/
    GameState & g_state;
    /** Finds command by its syntax and executes it*/
    int doCommand( string command_syntax );
    /** Kee[s reading commands from the terminal, until a command that terminates the current turn is executed*/
    bool readCommand();
    /** Frees allocated memory for known commands*/
    virtual ~CommandHandler();
};

