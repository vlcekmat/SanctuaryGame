#include <sstream>
#include <iostream>
#include <map>
#include "Commands.h"

using namespace std;

Command::Command(){}

Command::~Command(){}

// -------------------------------------------------------------------------------------------------------------------------

ExitCommand::ExitCommand() {
    syntax = "exit";
    description = "exits the application";
}

int ExitCommand::executeCommand() {
    return 3;
}

// -------------------------------------------------------------------------------------------------------------------------


// Help Command
HelpCommand::HelpCommand(map<string, Command*> & commands_map):all_commands(commands_map){
    syntax = "help";
    description = "shows all possible commands";
}

int HelpCommand::executeCommand(){
    auto map_iterator = all_commands.begin();
    cout << "\nAVAILABLE COMMANDS:\n\n";

    while( map_iterator != all_commands.end() ){

        cout << map_iterator->first << " - " << map_iterator->second->description << endl;
        map_iterator ++;
    }

    cout << endl;

    // returning 2 means that this command doesn't end turn
    return 2;
}

// -------------------------------------------------------------------------------------------------------------------------

// World Command - shows info about the world
WorldCommand::WorldCommand(GameState & game_state):g_state(game_state){
    syntax = "world";
    description = "prints information about the world";
}

int WorldCommand::executeCommand(){
    g_state.game_world.printGameWorld();
    return 2;
}

// -------------------------------------------------------------------------------------------------------------------------

// Buildings Command - shows info about constructable buildings
BuildingsCommand::BuildingsCommand(GameState & game_state):g_state(game_state){
    syntax = "buildings";
    description = "prints information about the constructable buildings";
}

int BuildingsCommand::executeCommand(){
    // for each building in the building pool print all required resources
    for (pair<string, Building*> building : g_state.building_pool.buildings){
        cout << "\033[1;36m   -" << building.first << "\033[0m" << endl;
        for ( pair<string, size_t> requirement : building.second->cost ){
            cout << "       " << requirement.first << ": " << requirement.second << endl;
        }
    }

    return 2;
}

// -------------------------------------------------------------------------------------------------------------------------

// Settlements Command - shows info about AI's settlements
SettlementsCommand::SettlementsCommand(GameState &game_state):g_state(game_state){
    syntax = "settlements";
    description = "prints information about raider settlements";
}

int SettlementsCommand::executeCommand() {
    cout << "\nRaider Settlements: " << endl;
    size_t index = 0;

    auto aiState = g_state.ai->getState()->settlements;

    for (const auto & settlement : aiState){
        cout << '[' << index << ']';
        cout << " - Soldiers: " << settlement->soldiers << endl;
        index ++;
    }

    cout << endl;
    return 2;
}

// -------------------------------------------------------------------------------------------------------------------------

HarvestCommand::HarvestCommand(GameState & game_state):g_state(game_state){
    syntax = "harvest";
    description = "{resource} - harvests specified resource";
}

int HarvestCommand::executeCommand(){

    string resource;
    cin >> resource;

    size_t num_modified;

    if (resource == "wood"){
        num_modified = g_state.game_world.modifyTrees((-1) * g_state.unemployed_people);
    }
    else if (resource == "stone") {
        num_modified = g_state.game_world.modifyRocks((-1) * g_state.unemployed_people);
    }   

    if (g_state.addResources(resource, num_modified * UNEMPLOYEDEFFECTIVITY ) != 0 
    && resource != "berries" 
    && resource != "animals" )
        return 1;
    else if (resource == "animals"){
        num_modified = g_state.game_world.modifyAnimals((-1) * g_state.unemployed_people);
        g_state.food += num_modified * ANIMALFOODVALUEC;
    }
    else if (resource == "berries"){
        num_modified = g_state.game_world.modifyBerries((-1) * g_state.unemployed_people);
        g_state.food += num_modified * BERRYFOODVALUEC;
    }

    return 0;
}

// -------------------------------------------------------------------------------------------------------------------------

// Build Command
BuildCommand::BuildCommand(GameState & game_state):g_state(game_state){
    syntax = "build";
    description = "{building_name} - builds specified building";
}

int BuildCommand::executeCommand(){
    string building_argument;
    cin >> building_argument;

    building_argument[0] = toupper(building_argument[0]);

    auto b_pool_it = g_state.building_pool.buildings.find(building_argument);

    // if specified building doesn't exist, return code 1 -> invalid command
    if( b_pool_it == g_state.building_pool.buildings.end() ){
        cout << "No such building: " << building_argument << '\n' << endl;
        return 2;
    }

    // check resources
    if ( !(g_state.checkResources( b_pool_it->second->cost )) ) {
        cout << "Insufficient Resources!\n" << endl;;
        return 2;
    }

    // buy for resources
    g_state.removeResources( b_pool_it->second->cost );

    // add new copy of the building to the constructed buildings pool in GameState
    g_state.addBuilding( building_argument, 0 );

    return 0;
}

// -------------------------------------------------------------------------------------------------------------------------

// Destroy Command
DestroyCommand::DestroyCommand(GameState & game_state):g_state(game_state){
    syntax = "destroy";
    description = "{building_index} - destroys";
}

int DestroyCommand::executeCommand(){
    string building_index_str;

    cin >> building_index_str;

    // check if the argument is a valid number
    for (char c : building_index_str){
        if (!isdigit(c))
            return 1;
    }

    // convert string to number
    stringstream ss_build_index(building_index_str);
    size_t building_index;
    ss_build_index >> building_index;

    // check invalid indexes
    if ( building_index >= g_state.buildings.size() ){
        return 1;
    }

    auto build_it = g_state.buildings.begin();

    for ( size_t i = 0; i < building_index; i++ )
        build_it ++;

    // move workers to unemployed people
    g_state.unemployed_people += (*build_it)->current_workers;
    
    cout << "\n\033[1;32m" << (*build_it)->name << " destroyed\033[0m\n" << endl;
    delete (*build_it);
    g_state.buildings.erase(build_it);

    return 0;
}

// -------------------------------------------------------------------------------------------------------------------------

// Employ Command
EmployCommand::EmployCommand(GameState & game_state):g_state(game_state){
    syntax = "employ";
    description = "{building_index} {employee_number} - (un)employs given ammount of people in the specified building";
}

int EmployCommand::executeCommand(){
    string building_index_str;
    string em_num_str;

    cin >> building_index_str;
    cin >> em_num_str;

    // check if both arguments are valid numbers
    for (char c : building_index_str){
        if (!isdigit(c))
            return 1;
    }

    for (char c : em_num_str){
        if (!isdigit(c) && c != '-')
            return 1;
    }

    // convert string to numbers
    stringstream ss_build_index(building_index_str);
    size_t building_index;
    ss_build_index >> building_index;

    stringstream ss_em_num(em_num_str);
    int em_num;
    ss_em_num >> em_num;

    // find building
    auto build_it = g_state.buildings.begin();

    // iterate to find indexed building
    while (building_index != 0 && build_it != g_state.buildings.end()){
        build_it ++;
        building_index --;
    }

    // invalid index
    if (build_it == g_state.buildings.end())
        return 1;

    // building found, modify with given number
    if ( building_index == 0 ){
        
        // figure out if I have enough unemployed people and modify em_num to fit
        if (em_num > (int)(g_state.unemployed_people))
            em_num = g_state.unemployed_people;

        int current_cap = (*build_it)->occupant_capacity - (*build_it)->current_workers;

        // wants to remove more people than there are in the building, remove all people
        if (( (int)((*build_it)->current_workers)) < em_num*(-1) && em_num < 0){
            g_state.unemployed_people += (*build_it)->current_workers;
            cout << "Unemployed " << (*build_it)->current_workers << " workers from " << (*build_it)->name << "\n" << endl;
            (*build_it)->current_workers = 0;
        }
        // wants to add more people than the current capacity allows, add as much as I can
        else if( em_num > current_cap ){
            (*build_it)->current_workers += current_cap;
            g_state.unemployed_people -= current_cap;

            cout << "Employed " << current_cap << " workers in " << (*build_it)->name << "\n" << endl;
        }
        // no special situations, apply em_num as given
        else {
            (*build_it)->current_workers += em_num;
            g_state.unemployed_people += (-1)*em_num;

            if ( em_num >= 0 )
                cout << "Employed " << em_num << " workers in " << (*build_it)->name << "\n" << endl;
            else if ( em_num < 0 )
                cout << "Unemployed " << em_num*(-1) << " workers in " << (*build_it)->name << "\n" << endl;
        }

    }
    else {
        // invalid index
        return 1;
    }

    return 0;
}

// -------------------------------------------------------------------------------------------------------------------------

// Attack Command
AttackCommand::AttackCommand(GameState & game_state):g_state(game_state){
    syntax = "attack";
    description = "{raider_settlement_index} {soldier_amount} - sends the given amount of soldiers to attack the specified settlement";
}

int AttackCommand::executeCommand() {
    string settlement_index_str;
    string sol_num_str;

    cin >> settlement_index_str;
    cin >> sol_num_str;

    // check if both arguments are valid numbers
    for (char c : settlement_index_str){
        if (!isdigit(c))
            return 1;
    }

    for (char c : sol_num_str){
        if (!isdigit(c) && c != '-')
            return 1;
    }

    // convert string to numbers
    stringstream ss_settlement_index(settlement_index_str);
    size_t settlement_index;
    ss_settlement_index >> settlement_index;

    stringstream ss_sol_num(sol_num_str);
    size_t sol_num;
    ss_sol_num >> sol_num;

    if (sol_num > g_state.soldiers){
        sol_num = g_state.soldiers;
    }

    if (sol_num <= 0){
        cout << "You cannot attack with 0 soldiers... Draft some first!" << endl;
        return 1;
    }

    // find settlement
    auto aiState = g_state.ai->getState();
    auto settlement_it = aiState->settlements.begin();

    // iterate to find indexed settlement
    while (settlement_index != 0 && settlement_it != aiState->settlements.end()){
        settlement_it ++;
        settlement_index --;
    }

    // invalid index
    if (settlement_it == aiState->settlements.end())
        return 1;

    // settlement found, initiate battle
    if ( settlement_index == 0){
        auto combatResults = Combat::evaluateCombat(sol_num, (*settlement_it)->soldiers);
        (*settlement_it)->soldiers -= combatResults.raiderCasualties;
        g_state.soldiers -= combatResults.playerCasualties;
        g_state.people -= combatResults.playerCasualties;

        // if settlement has 0 soldiers, destroy it
        if ((*settlement_it)->soldiers <= 0){
            cout << "Raider settlement has been destroyed! Yay!" << endl;
            aiState->settlements.erase(settlement_it);
        }
    }
    else {
        // invalid index
        return 1;
    }

    return 0;
}

// -------------------------------------------------------------------------------------------------------------------------

//  Wait Command
WaitCommand::WaitCommand(){
    syntax = "wait";
    description = "ends turn without doing anything";
}

// does literally nothing
int WaitCommand::executeCommand(){
    return 0;
}

// -------------------------------------------------------------------------------------------------------------------------

// Save Command
SaveCommand::SaveCommand(GameState & game_state):g_state(game_state){
    syntax = "save";
    description = "{save_path} - saves game into a specified path";
}

int SaveCommand::executeCommand(){
    string path;
    cin >> path;
    g_state.saveFile(path);
    return 2;
}

// -------------------------------------------------------------------------------------------------------------------------

// Load Command
LoadCommand::LoadCommand(GameState & game_state):g_state(game_state){
    syntax = "load";
    description = "{load_path} - loads game from the specified path";
}

int LoadCommand::executeCommand(){
    string path;
    cin >> path;
    try {
        if (!g_state.loadSaveFile(path))
            return 3;
    }
    catch(const char * exc){
        cout << "\n" << path << ": " << exc << "\n" << endl;
        return 2;
    }

    g_state.printGameState();

    return 2;
}

// -------------------------------------------------------------------------------------------------------------------------

// Action Command

ActionCommand::ActionCommand() = default;

int ActionCommand::executeCommand() {
    map<string, int> parameters;

    for (const auto & parameter : action->parameterMap){
        string argument_str;
        cin >> argument_str;

        // check if argument is a valid number
        for (char c : argument_str){
            if (!isdigit(c))
                return 1;
        }

        // convert string to numbers
        stringstream ss_argument(argument_str);
        int argument;
        ss_argument >> argument;


        parameters.emplace(parameter.second, argument);
    }

    action->applyEffects(parameters);

    return 0;
}
