#include "Building.h"
#include "../EffectHandler/EffectHandler.h"

Building::Building(){}
Building::~Building(){}

BuildingPool::BuildingPool(){

}
BuildingPool::~BuildingPool(){ 
    for ( pair<string, Building*> item : buildings ){
        if (item.second != nullptr)
            delete (item.second);
        item.second = nullptr;
    }
}

