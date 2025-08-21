#include <iostream>
#include <memory>
#include "./DecisionTree.h"

#pragma once

using namespace std;

/** @brief Class containing state and behavior of the AI player*/
class AI{
public:
    AI();

    /** Activates the first node in the decision tree*/
    virtual void makeDecision(bool & combatFlag, size_t & reference);
    /** Returns the current state of AI, such as population*/
    virtual shared_ptr<AIState> getState();
    /** Prints the ai state to the console*/
    virtual void printState();

    virtual ~AI();

private:
    /** Object containing behavior and data*/
    shared_ptr<DecisionTree> decisionTree;
};

