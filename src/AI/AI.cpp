#include "AI.h"

using namespace std;

AI::AI() {
    decisionTree = make_shared<DecisionTree>();
}

void AI::makeDecision(bool & combatFlag, size_t & reference) {
    decisionTree->traverseTree(combatFlag, reference);
}

shared_ptr<AIState> AI::getState() {
    return decisionTree->getState();
}

void AI::printState(){
    auto state = getState();
    cout << "AI resources: " << state->resources << endl;
}

AI::~AI() {

}