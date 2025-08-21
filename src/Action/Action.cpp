#include "./Action.h"

Action::Action(EventHandler & eventHandler): eventHandler(eventHandler) {

}

void Action::applyEffects(const map<string, int> &parameters) {
    for (const auto & effect : effects){
        auto parameterNameIt = parameterMap.find(effect);
        if (parameterNameIt != parameterMap.end()){
            auto parameterIt = parameters.find(parameterNameIt->second);

            if (parameterIt != parameters.end()){
                eventHandler.eff_han->callEffect(effect, parameterIt->second, 1);
            }
        }
        else {
            auto staticParameterIt = staticParameters.find(effect);
            if (staticParameterIt != staticParameters.end()){
                eventHandler.eff_han->callEffect(effect, staticParameterIt->second, 1);
            }
        }

    }
}

Action::~Action() {}

// -----------------------------------------------------------------------------------


ActionPool::ActionPool() {

}

ActionPool::~ActionPool() {}
