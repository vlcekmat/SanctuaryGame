#include <iostream>
#include <set>
#include <string>
#include <memory>
#include <list>
#include <random>
#include "./AIState.h"

#pragma once

using namespace std;

/** Constant defining the minimum amount of resources needed before AI starts considering building*/
#define BUILD_THRESHOLD 50
/** Constant defining the maximum amount of resources after which AI stops harvesting resources*/
#define COLLECT_THRESHOLD 200
/** Constant defining the minimum amount of raiders in a settlement needed before AI starts considering raiding*/
#define RAID_THRESHOLD 4

/** Constant defining the cost of AI settlements in resources*/
#define SETTLEMENT_COST 25

/** Constant defining the amount of soldiers in a newly built settlement*/
#define INITIAL_SETTLEMENT_SOLDIERS 1

/** Constant defining how quickly AI recruits new raiders*/
#define REGROUP_POWER 2
/** Constant defining how quickly AI collects resources*/
#define COLLECT_EFFICIENCY 2

/** @brief Base class for all decision nodes
 *
 *  Represents a decision state, which can either carry out an operation,
 *  or dive into another node
 *
*/
class Node{
public:
    Node();

    /** Tries activating this node, checks for base conditions. Returns true if activating, false otherwise*/
    virtual bool tryNode(bool & combatFlag, size_t & reference) = 0;

    /** current state of ai including information, such as current population*/
    shared_ptr<AIState> aiState;

    /** certainty that this node activates, when base conditions are met*/
    double randModifier;

    /** Evaluates probability of the action and determines if it is happening or not*/
    virtual bool evaluateActionWithProbability();

    virtual ~Node();

protected:
    /** nodes that can follow*/
    list<unique_ptr<Node>> children;
};

// -------------------------------------------------------------------------------------------------------------------------

/** @brief The first node in the decision tree that is activated*/
class RootNode : public Node{

public:

    RootNode(shared_ptr<AIState> _aiState);

    virtual bool tryNode(bool & combatFlag, size_t & reference) override;
};

// -------------------------------------------------------------------------------------------------------------------------

/** @brief Node that builds a new raider settlement*/
class BuildNode : public Node{
public:

    BuildNode(shared_ptr<AIState> _aiState, const double & _randModifier);

    virtual bool tryNode(bool & combatFlag, size_t & reference) override;
};

// -------------------------------------------------------------------------------------------------------------------------

/** @brief Node that collects resources for raiders*/
class CollectNode : public Node{
public:

    CollectNode(shared_ptr<AIState> _aiState, const double & _randModifier);

    virtual bool tryNode(bool & combatFlag, size_t & reference) override;
};

// -------------------------------------------------------------------------------------------------------------------------

/** @brief Node that recruits new raiders to a random settlement*/
class RegroupNode : public Node{
public:

    RegroupNode(shared_ptr<AIState> _aiState, const double & _randModifier);

    virtual bool tryNode(bool & combatFlag, size_t & reference) override;
};

// -------------------------------------------------------------------------------------------------------------------------

/** @brief Node that sends raider attackers to the player*/
class RaidNode : public Node{
public:

    RaidNode(const shared_ptr<AIState> & _aiState, const double & _randModifier);

    virtual bool tryNode(bool & combatFlag, size_t & reference) override;

private:

    /** Tries to find a settlement suitable for drafting attacking raiders*/
    pair<size_t, bool> findSettlementWithMinPop();
};

// -------------------------------------------------------------------------------------------------------------------------

/** @brief Last node, if the AI can't decide on what to do, it stays idle*/
class IdleNode : public Node{
public:

    IdleNode();

    virtual bool tryNode(bool & combatFlag, size_t & reference) override;
};

// -------------------------------------------------------------------------------------------------------------------------


class DecisionTree{
public:
    DecisionTree();

    /** First node in the tree that should always activate*/
    unique_ptr<RootNode> rootNode;

    /** Activates the root node*/
    virtual void traverseTree(bool & combatFlag, size_t & reference);

    virtual shared_ptr<AIState> getState();

    virtual ~DecisionTree();

protected:
    /** current state of ai including information, such as current population*/
    shared_ptr<AIState> aiState;
};

// ---------------------------------------------------------------------------

