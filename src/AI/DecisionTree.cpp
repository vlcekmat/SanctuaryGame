#include "DecisionTree.h"
#include <iostream>

using namespace std;

Node::Node(){}

bool Node::evaluateActionWithProbability() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    double randomNum = dis(gen);
    return randomNum <= randModifier;
}

Node::~Node() {}
// ---------------------------------------------------------------------------------------

RootNode::RootNode(shared_ptr<AIState> _aiState) {
    aiState = _aiState;

    //connect children nodes
    children.push_back(make_unique<BuildNode>(aiState, 0.1));
    children.push_back(make_unique<RegroupNode>(aiState, 0.4));
    children.push_back(make_unique<CollectNode>(aiState,0.8));
    children.push_back(make_unique<RaidNode>(aiState, 0.2));
    children.push_back(make_unique<IdleNode>());

    for (const auto & child : children){
        child->aiState = aiState;
    }

    randModifier = 1;
}

bool RootNode::tryNode(bool & combatFlag, size_t & reference) {
    // traverse children
    for (const auto & child : children){
        if (child->tryNode(combatFlag, reference))
            break;
    }
    return true;
}

// ---------------------------------------------------------------------------------------

BuildNode::BuildNode(shared_ptr<AIState> _aiState, const double & _randModifier) {
    aiState = _aiState;
    randModifier = _randModifier;
}

bool BuildNode::tryNode(bool & combatFlag, size_t & reference) {
    if (aiState->resources >= BUILD_THRESHOLD && evaluateActionWithProbability()){
        aiState->resources -= SETTLEMENT_COST;
        aiState->settlements.push_back(make_shared<Settlement>(INITIAL_SETTLEMENT_SOLDIERS));
        aiState->population += INITIAL_SETTLEMENT_SOLDIERS;

        cout << "AI: Building a settlement" << endl;
        return true;
    }
    else
        return false;
}

// ---------------------------------------------------------------------------------------

CollectNode::CollectNode(shared_ptr<AIState> _aiState, const double & _randModifier) {
    aiState = _aiState;
    randModifier = _randModifier;
}

bool CollectNode::tryNode(bool & combatFlag, size_t & reference) {
    if (aiState->resources <= COLLECT_THRESHOLD && evaluateActionWithProbability()){
        cout << "AI: Collecting resources" << endl;
        aiState->resources += aiState->population * COLLECT_EFFICIENCY;
        return true;
    }
    else
        return false;
}

// ---------------------------------------------------------------------------------------

RegroupNode::RegroupNode(shared_ptr<AIState> _aiState, const double &_randModifier) {
    aiState = _aiState;
    randModifier = _randModifier;
}

bool RegroupNode::tryNode(bool & combatFlag, size_t & reference) {
    if (!aiState->settlements.empty() && evaluateActionWithProbability()){
        // pick random settlement index
        size_t index = rand() % (aiState->settlements.size());

        // get to the index
        auto settlement_it = aiState->settlements.begin();
        while (index != 0){
            settlement_it ++;
            index --;
        }

        // add population to the settlement
        (*settlement_it)->soldiers += REGROUP_POWER;

        // add to the overall population
        aiState->population += REGROUP_POWER;

        cout << "AI: regrouping - " << REGROUP_POWER << " new raiders have been recruited" << endl;

        return true;
    }
    else
        return false;
}

// ---------------------------------------------------------------------------------------

RaidNode::RaidNode(const shared_ptr<AIState> & _aiState, const double & _randModifier) {
    aiState = _aiState;
    randModifier = _randModifier;
}

bool RaidNode::tryNode(bool & combatFlag, size_t & reference) {
    auto minPopSettlement = findSettlementWithMinPop();

    if (evaluateActionWithProbability() && minPopSettlement.second){
        // conditions met, raid player
        cout << "AI: raiding the player" << endl;

        combatFlag = true;
        reference = minPopSettlement.first;
        return true;
    }
    else{
        return false;
    }
}

pair<size_t, bool> RaidNode::findSettlementWithMinPop() {
    size_t index = 0;
    for (auto & settlement : aiState->settlements){
        if (settlement->soldiers >= RAID_THRESHOLD) {
            // found settlement with min required amount of soldiers
            pair<size_t, bool> toReturn(index, true);
            return toReturn;
        }
        index ++;
    }

    pair<size_t, bool> toReturn = {0, false};
    return toReturn;
}

// ---------------------------------------------------------------------------------------

IdleNode::IdleNode() {
    randModifier = 1;
}

bool IdleNode::tryNode(bool & combatFlag, size_t & reference) {
    cout << "AI: is idle" << endl;
    return true;
}


// ---------------------------------------------------------------------------------------


DecisionTree::DecisionTree(): aiState(make_shared<AIState>()){
    // load this from save files later
    rootNode = make_unique<RootNode>(aiState);
}

void DecisionTree::traverseTree(bool & combatFlag, size_t & reference) {
    rootNode->tryNode(combatFlag, reference);
}

shared_ptr<AIState> DecisionTree::getState() {
    return aiState;
}

DecisionTree::~DecisionTree() {
}

// ---------------------------------------------------------------------------------------