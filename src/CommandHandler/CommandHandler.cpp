#include <iostream>
#include "CommandHandler.h"
#include "../JsonParser/JsonParser.h"

using namespace std;


CommandHandler::CommandHandler(GameState & game_state, EventHandler & event_handler):g_state(game_state){
    // initialize all commands

    ExitCommand * exit_command = new ExitCommand();
    commands.insert({exit_command->syntax, exit_command});

    HelpCommand * help_command = new HelpCommand(CommandHandler::commands);
    commands.insert( { help_command->syntax, help_command } );

    WorldCommand * world_command = new WorldCommand(g_state);
    commands.insert( { world_command->syntax, world_command } );

    BuildingsCommand * buildings_command = new BuildingsCommand(g_state);
    commands.insert( { buildings_command->syntax, buildings_command } );

    SettlementsCommand * settlements_command = new SettlementsCommand(g_state);
    commands.insert( { settlements_command->syntax, settlements_command } );

    BuildCommand * build_command = new BuildCommand(g_state);
    commands.insert( { build_command->syntax, build_command } );

    DestroyCommand * destroy_command = new DestroyCommand(g_state);
    commands.insert( { destroy_command->syntax, destroy_command } );

    HarvestCommand * harvest_command = new HarvestCommand(g_state);
    commands.insert( { harvest_command->syntax, harvest_command } );

    EmployCommand * employ_command = new EmployCommand(g_state);
    commands.insert( { employ_command->syntax, employ_command } );

    AttackCommand * attack_command = new AttackCommand(g_state);
    commands.insert( {attack_command->syntax, attack_command} );

    SaveCommand * save_command = new SaveCommand(g_state);
    commands.insert( { save_command->syntax, save_command } );

    LoadCommand * load_command = new LoadCommand(g_state);
    commands.insert( { load_command->syntax, load_command } );

    WaitCommand * wait_command = new WaitCommand();
    commands.insert( { wait_command->syntax, wait_command } );


    // initialize action commands
    actionPool = make_unique<ActionPool>();

    try{
        JsonParser::parseActions(*actionPool, event_handler);
    }
    catch(...){
        for (auto & command : commands){
            delete command.second;
        }
        throw "InvalidJsonException";
    }

    for (const auto & action : actionPool->actions){
        ActionCommand * action_command = new ActionCommand();
        action_command->syntax = action->syntax;
        action_command->description = action->description;
        action_command->action = action;
        commands.insert( { action_command->syntax, action_command } );
    }
}

int CommandHandler::doCommand( string command_syntax ){

    auto commands_iterator = CommandHandler::commands.find( command_syntax );

    if ( commands_iterator == CommandHandler::commands.end() ){
        return 1;
    }

    Command * to_execute = commands_iterator->second;
    
    return to_execute->executeCommand();
}

bool CommandHandler::readCommand(){
    string current_command;
    bool ends_turn = false;

    while (!ends_turn){
        cin >> current_command;

        int command_state = (*this).doCommand(current_command);

        // 1 = error, 0 = ends turn, 2 = doesn't end turn, 3 = exits application

        if ( command_state == 1 ){
            cout << "\n" << "INVALID COMMAND!\n" << endl;
        }

        else if ( command_state == 0 ){
            ends_turn = true;
            break;
        }

        else if (command_state == 3){
            // end application
            return false;
        }

    }

    // continue application
    return true;
}

CommandHandler::~CommandHandler()
{
    auto commands_iterator = CommandHandler::commands.begin();

    while ( commands_iterator != CommandHandler::commands.end() ){

        delete (commands_iterator->second);
        commands_iterator ++;
    }
}