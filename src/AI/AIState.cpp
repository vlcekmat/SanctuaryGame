#include "AIState.h"

using namespace std;

AIState::AIState(): population(1), resources(0) {
    settlements.push_back(make_shared<Settlement>(1));
}

AIState::~AIState() {}