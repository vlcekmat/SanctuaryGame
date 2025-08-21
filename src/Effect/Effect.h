#include <iostream>
#include <string>
#include "../GameState/GameState.h"

#pragma once

/** Constant defining how much food do we get from one animal using effects*/
#define ANIMALFOODVALUE 5
/** Constant defining how much food do we get from one berry using effects*/
#define BERRYFOODVALUE 2

using namespace std;

/** @brief Class that defines world effects. Could be an effect of a building, or an effect of a global event. Could also be used by actions and commands*/
class Effect{  
public:
    Effect();

    string effect_name;
    virtual void applyEffect(int value) = 0;

    virtual ~Effect();
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// derived effects follow here

/** @brief Effect that modifies wood resources without chopping/seeding trees*/
class ModWood : public Effect{
public:
    ModWood( GameState & game_state );
    GameState & g_state;
    virtual void applyEffect(int value) override;
    virtual ~ModWood();
};
// ----------------------------------------------------------------------------------------------------------------------------------------------------
/** @brief Effect that chops trees down and collects wood*/
class ChopTrees : public Effect{
public:
    ChopTrees( GameState & game_state );
    GameState & g_state;
    virtual void applyEffect(int value) override;
    virtual ~ChopTrees();
};
// ----------------------------------------------------------------------------------------------------------------------------------------------------
/** @brief Effect that mines rocks and collects stone*/
class MineRocks : public Effect{
public:
    MineRocks( GameState & game_state );
    GameState & g_state;
    virtual void applyEffect(int value) override;
    virtual ~MineRocks();
};
// ----------------------------------------------------------------------------------------------------------------------------------------------------
/** @brief Effect that modifies stone resources without mining out rocks*/
class ModStone : public Effect{
public:
    ModStone( GameState & game_state );
    GameState & g_state;
    virtual void applyEffect(int value) override;
    virtual ~ModStone();
};
// ----------------------------------------------------------------------------------------------------------------------------------------------------
/** @brief Effect that modifies trees without affecting resources*/
class ModTrees : public Effect{
public:
    ModTrees( GameState & game_state );
    GameState & g_state;
    virtual void applyEffect(int value) override;
    virtual ~ModTrees();
};
// ----------------------------------------------------------------------------------------------------------------------------------------------------
/** @brief Effect that modifies rocks without affecting resources*/
class ModRocks : public Effect{
public:
    ModRocks( GameState & game_state );
    GameState & g_state;
    virtual void applyEffect(int value) override;
    virtual ~ModRocks();
};
// ----------------------------------------------------------------------------------------------------------------------------------------------------
/** @brief Effect that modifies animals without affecting resources*/
class ModAnimals : public Effect{
public:
    ModAnimals( GameState & game_state );
    GameState & g_state;
    virtual void applyEffect(int value) override;
    virtual ~ModAnimals();
};
// ----------------------------------------------------------------------------------------------------------------------------------------------------
/** @brief Effect that takes berries and collects food*/
class GatherBerries : public Effect{
public:
    GatherBerries( GameState & game_state );
    GameState & g_state;
    virtual void applyEffect(int value) override;
    virtual ~GatherBerries();
};
// ----------------------------------------------------------------------------------------------------------------------------------------------------
/** @brief Effect that hunts animals and collects food*/
class HuntAnimals : public Effect{
public:
    HuntAnimals( GameState & game_state );
    GameState & g_state;
    virtual void applyEffect(int value) override;
    virtual ~HuntAnimals();
};
// ----------------------------------------------------------------------------------------------------------------------------------------------------
/** @brief Effect that modifies berries without affecting resources*/
class ModBerries : public Effect{
public:
    ModBerries( GameState & game_state );
    GameState & g_state;
    virtual void applyEffect(int value) override;
    virtual ~ModBerries();
};
// ----------------------------------------------------------------------------------------------------------------------------------------------------
/** @brief Effect that raises the population capacity*/
class Housing : public Effect{
public:
    Housing( GameState & game_state );
    GameState & g_state;
    virtual void applyEffect(int value) override;
    virtual ~Housing();
};
// ----------------------------------------------------------------------------------------------------------------------------------------------------
/** @brief Effect that raises population if there is capacity*/
class StrangerArrives : public Effect{
public:
    StrangerArrives( GameState & game_state );
    GameState & g_state;
    virtual void applyEffect(int value) override;
    virtual ~StrangerArrives();
};
// ----------------------------------------------------------------------------------------------------------------------------------------------------
/** @brief Effect that kills people*/
class KillPeople : public Effect{
public:
    KillPeople( GameState & game_state );
    GameState & g_state;
    virtual void applyEffect(int value) override;
    virtual ~KillPeople();
};
// ----------------------------------------------------------------------------------------------------------------------------------------------------
/** @brief Effect that destroys buildings*/
class DestroyBuildings : public Effect{
public:
    DestroyBuildings( GameState & game_state );
    GameState & g_state;
    virtual void applyEffect(int value) override;
    virtual ~DestroyBuildings();
};
// ----------------------------------------------------------------------------------------------------------------------------------------------------
/** @brief Effect that drafts people into the army*/
class Draft : public Effect{
public:
    Draft( GameState & gameState );
    GameState & g_state;
    virtual void applyEffect(int value) override;
    virtual ~Draft();
};
// ----------------------------------------------------------------------------------------------------------------------------------------------------
/** @brief Effect that undrafts people*/
class Undraft : public Effect{
public:
    Undraft( GameState & gameState );
    GameState & g_state;
    virtual void applyEffect(int value) override;
    virtual ~Undraft();
};